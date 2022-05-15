#ifndef WEBSOCKET_HPP
# define WEBSOCKET_HPP
# include <sys/socket.h>
# include <netinet/in.h>

// Base abstract socket class.
class WebSocket
{
private:
	// Tests whether the connection is established or not
	void testConnection(int32_t item_to_test);

protected:
	struct sockaddr_in address;
	int32_t sock;
	int32_t connection;

	// Determines the socket mode:
	// - passive (binding to an address)
	// - or active (connecting to an address)
	virtual int32_t connectToNetwork(int32_t sock, struct sockaddr_in address) = 0;

public:
	WebSocket(
		int32_t port,
		uint32_t interface);

	int getSocket();

	virtual ~WebSocket() = 0;
};

#endif
