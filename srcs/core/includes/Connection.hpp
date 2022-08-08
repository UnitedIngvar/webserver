#ifndef CONNECION_HPP
# define CONNECION_HPP

#include "Core.hpp"

class Connection
{
private:
	socket_fd	_connectionSocket;
	bool		_isClosed;

public:
	Connection(socket_fd connectionSocket);
	~Connection();
	void	closeConnection();

	socket_fd	getSocket() const;
};

#endif
