#ifndef BINDINGSOCKET_HPP
# define BINDINGSOCKET_HPP
#include <sys/socket.h>
#include <netinet/in.h>

class BindinSocket : public WebSocket
{
private:

public:
	BindinSocket(int32_t domain, int32_t service, int32_t protocol,
		int32_t port, uint32_t interface);

	virtual ~BindinSocket();
};

#endif
