#include "WebSocket.hpp"
#include <sys/socket.h>
#include <netinet/in.h>

WebSocket::WebSocket(int domain, int service, int protocol)
{
	connection = socket(domain, service, protocol);

}

WebSocket::~WebSocket()
{

}
