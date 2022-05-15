#include "BindingSocket.hpp"

BindinSocket::BindinSocket(int32_t domain, int32_t service, int32_t protocol,
	int32_t port, uint32_t interface)
	: WebSocket(domain, service, protocol, port, interface)
{

}

int32_t connectToNetwork(int32_t sock, struct sockaddr_in address)
{
	return bind(sock, (struct sockaddr *)&address, sizeof(address));
}
