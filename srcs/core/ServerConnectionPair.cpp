#include "ServerConnectionPair.hpp"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// CONSTRUCTOR / DESTRUCTOR
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ServerConnectionPair::ServerConnectionPair(
	Server const &server,
	Connection const &connection) :
	_server(&server),
	_connection(&connection)
{

}


ServerConnectionPair::~ServerConnectionPair()
{

}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// ACCESS MEMBER FUNCIONS
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Server		const &ServerConnectionPair::getServer() const { return *_server; }
Connection	const &ServerConnectionPair::getConnection() const { return *_connection; }
