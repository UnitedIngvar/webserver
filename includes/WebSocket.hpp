#ifndef WEBSOCKET_HPP
# define WEBSOCKET_HPP
#include <sys/socket.h>
#include <netinet/in.h>

class WebSocket
{
private:
	struct sockaddr_in address;
	int connection;

public:
	WebSocket(
		int domain,
		int service,
		int protocol,
		int port);

	~WebSocket();
};

#endif
