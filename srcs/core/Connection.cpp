#include "Connection.hpp"
#include "unistd.h"

Connection::Connection(
	socket_fd connectionSocket) :
	_connectionSocket(connectionSocket),
	_isClosed(false)
{

}

Connection::~Connection()
{
	// TODO: we might want to close connection here
}

void	Connection::closeConnection()
{
	if (_isClosed)
		return;

	_isClosed = true;
	close(_connectionSocket);
}

socket_fd	Connection::getSocket() const { return _connectionSocket; }
