#ifndef WEBSOCKET_HPP
# define WEBSOCKET_HPP
#include <sys/socket.h>
#include <netinet/in.h>

class WebSocket
{
private:
	struct sockaddr_in address;
	int32_t sock;
	int32_t connection;

public:
	WebSocket(int32_t domain, int32_t service, int32_t protocol,
		int32_t port, uint32_t interface);

	virtual int32_t connectToNetwork(int32_t sock, struct sockaddr_in address) = 0;
	void testConnection(int32_t item_to_test);

	virtual ~WebSocket() = 0;
};

#endif
