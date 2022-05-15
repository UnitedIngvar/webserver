#include "WebSocket.hpp"

WebSocket::WebSocket(int32_t domain, int32_t service, int32_t protocol,
	int32_t port, uint32_t interface)
{
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htons(interface);
	sock = socket(domain, service, protocol);
	connection = connectToNetwork(sock, address);
	testConnection(connection);
}

void WebSocket::testConnection(int32_t item_to_test)
{
	if (item_to_test < 0)
	{
		// TODO: print log into a file
		exit(EXIT_FAILURE);
	}
}

WebSocket::~WebSocket()
{

}
