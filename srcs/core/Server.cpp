#include "Server.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

Server::Server(ServerConfiguration const &config)
	: _config(config)
{
	_logger = Logger::getInstance();
	if (_logger)
	{
		std::invalid_argument("singleton Logger is not initialized!");
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
	char buffer[RECV_SIZE] = {0};

	socket_fd socket = clientConnection.getSocket();
	int recieved = ::recv(socket, buffer, RECV_SIZE - 1, 0);
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
		clientConnection.closeConnection();
		return;
	}

	std::string requestStr(buffer, recieved);
	Request *request = _requestFactory.create(requestStr);

	ResponseCode responseCode;
	if (_requestValidator.validateRequest(request, responseCode) == false)
	{
		delete request;
		// todo: build appropriate response
	}

	Error *err = nullptr;
	IGateway &gateway = _gatewayFactory.create(request, _config, err);
	if (err != nullptr)
	{
		delete request;
		delete err;
		// todo: build appropriate response
	}

	Response *response = gateway.processRequest(request, err);
	if (err != nullptr)
	{
		delete request;
		delete err;
		// todo: build appropriate response
	}
	std::string responseString = response->toResponseString();
	int	symbolsSent = ::send(socket, responseString.c_str(), responseString.size(), 0);
	if (symbolsSent < responseString.size())
	{
		_logger->logWarning("server sent only " +
		std::to_string(symbolsSent) + " bites out of " +
		std::to_string(responseString.size()));
	}

	delete response;
	delete request;
	clientConnection.closeConnection();
}
