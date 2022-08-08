#include "Server.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

Server::Server(ServerConfiguration const &config) :
	_config(config),
	_errorResponseBuilder(config)
{
	_logger = Logger::getInstance();
	if (_logger)
	{
		std::invalid_argument("singleton Logger is not initialized!");
	}
}

Request	*Server::readRequest(Connection const &clientConnection)
{
	char buffer[RECV_SIZE] = {0};

	int recieved = ::recv(clientConnection.getSocket(), buffer, RECV_SIZE - 1, 0);
	if (recieved <= 0)
	{
		if (recieved == 0)
		{
			_logger->logInfo("Connection was closed by client");
		}
		if (recieved == -1)
		{
			_logger->logWarning("Read error, closing connection");
		}
		return nullptr;
	}

	std::string rawRequest(buffer, recieved);
	return _requestFactory.create(rawRequest);
}

void	Server::sendResponse(Response const *response, Connection const &connection) const
{
	std::string responseString = response->toResponseString();
	int	symbolsSent = ::send(connection.getSocket(), responseString.c_str(), responseString.size(), 0);

	if (symbolsSent < responseString.size())
	{
		_logger->logWarning("server sent only " +
		std::to_string(symbolsSent) + " bites out of " +
		std::to_string(responseString.size()));
	}
}

socket_fd	Server::getListenSocket() const { return _listenSocket; }

void		Server::startListening(Error *error)
{
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	if ((_listenSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		error = new Error(
			"Error while creating socket for " +
			std::to_string(_config.host) + ":" + std::to_string(_config.port));
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(_config.host);
	address.sin_port = htons(_config.port);

	memset(address.sin_zero, '\0', sizeof address.sin_zero);

	if (bind(_listenSocket, (struct sockaddr *)&address, addrlen) < 0)
	{
		error = new Error(
			"Error while binding socket " + std::to_string(_listenSocket) + " to " +
			std::to_string(_config.host) + ":" + std::to_string(_config.port));
	}
	if (listen(_listenSocket, 10) < 0)
	{
		error = new Error(
			"Error while making socket " + std::to_string(_listenSocket) + " a listening socket");
	}
}

void		Server::handleConnection(Connection &clientConnection)
{
	Request *request = readRequest(clientConnection);
	if (request == nullptr)
	{
		return;
	}

	Error *err = nullptr;
	if (_requestValidator.validateRequest(request, err) == false)
	{
		delete request;
		// todo: build appropriate response
	}

	IGateway &gateway = _gatewayFactory.create(request, _config, err);
	if (err != nullptr)
	{
		Response *response = _errorResponseBuilder.build(err);

		sendResponse(response, clientConnection);
		delete response;
		delete request;
		delete err;
		return;
	}

	Response *response = gateway.processRequest(request, err);
	if (err != nullptr)
	{
		if (response == nullptr)
		{
			response = _errorResponseBuilder.build(err);
		}

		sendResponse(response, clientConnection);
		delete response;
		delete request;
		delete err;
		return;
	}

	sendResponse(response, clientConnection);
	clientConnection.closeConnection();
	delete request;
	delete response;
}
