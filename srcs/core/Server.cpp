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

void		Server::startListening(Error *error)
{
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	if ((_listenSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		error = new Error(
			"Error while creating socket for host" + std::to_string(_listenSocket) + " to port " + std::to_string(_config.port));
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(_config.host);
	address.sin_port = htons(_config.port);

	memset(address.sin_zero, '\0', sizeof address.sin_zero);

	if (bind(_listenSocket, (struct sockaddr *)&address, addrlen) < 0)
	{
		error = new Error(
			"Error while binding socket " + std::to_string(_listenSocket) + " to " +
			std::string(_config.host) + ":" + std::string(_config.port));
	}
	if (listen(_listenSocket, 10) < 0)
	{
		error = new Error(
			"Error while making socket " + std::to_string(_listenSocket) + " a listening socket");
	}
}

void		Server::handleConnection(socket_fd clientConnection)
{

}
