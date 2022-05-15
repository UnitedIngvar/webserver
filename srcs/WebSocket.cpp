#include "WebSocket.hpp"
#include <iostream>

WebSocket::WebSocket(
	int32_t port,
	uint32_t interface)
{
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htons(interface);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	testConnection(sock);
}

int		WebSocket::getSocket() { return sock; }

void	WebSocket::testConnection(
	int32_t item_to_test)
{
	if (item_to_test < 0)
	{
		// TODO: use logger
		std::cout << "Error on connection" << std::endl;
		// TODO: use error code
		exit(1);
	}
}

WebSocket::~WebSocket()
{
}
