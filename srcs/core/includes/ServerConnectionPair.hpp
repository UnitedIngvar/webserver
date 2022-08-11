#ifndef SERVER_CONNECTION_PAIR_HPP
# define SERVER_CONNECTION_PAIR_HPP

# include "Server.hpp"
# include "Connection.hpp"

class ServerConnectionPair
{
private:
	Server		const *_server;
	Connection	const *_connection;

public:
	ServerConnectionPair(
		Server const &server,
		Connection const &connection);
	~ServerConnectionPair();

	Server		const &getServer() const;
	Connection	const &getConnection() const;
};

#endif
