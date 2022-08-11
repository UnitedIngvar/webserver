#ifndef KQUEUE_POLLER_HPP
# define KQUEUE_POLLER_HPP

# include <stdlib.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/event.h>
# include <unistd.h>
# include <vector>
# include "ServerConnectionPair.hpp"

class KqueuePoller
{
private:
	int				_kqueue;
	struct kevent	_changeEvent[4];
	struct kevent	_event[4];

public:
	KqueuePoller(Server servers[]);
	~KqueuePoller();

	ServerConnectionPair *pollConnections();
};

#endif
