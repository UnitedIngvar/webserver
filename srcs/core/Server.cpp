#include "Server.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

Server::Server(ServerConfiguration const &config)
	: _config(config)
{

}

socket_fd	Server::getListenSocket() const { return _listenSocket; }

void		startListening(Error *error)
{
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	if ((_listenSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("In socket");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(config.);
	address.sin_port = htons(config.port);

	memset(address.sin_zero, '\0', sizeof address.sin_zero);

	if (bind(_listenSocket, (struct sockaddr *)&address, addrlen) < 0)
	{
		_logger.logError(
			"Error while binding socket " + std::to_string(_listenSocket) + " to port " + std::string(config.port));
	}
	if (listen(_listenSocket, 10) < 0)
	{
		_logger.logError(
			"Error while making socket " + std::to_string(_listenSocket) + " a listening socket");
	}
}

void		Server::handleConnection(socket_fd clientConnection)
{

}
