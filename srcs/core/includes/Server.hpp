#ifndef SERVER_HPP
# define SERVER_HPP

# include "Configuration.hpp"
# include "GatewayFactory.hpp"
# include "RequestValidator.hpp"
# include "RequestFactory.hpp"
# include "Connection.hpp"
# include "Logger.hpp"
# include "Core.hpp"

# define RECV_SIZE 65536

class Server
{
private:
	// initialized dynamicaly
	ServerConfiguration	_config;
	socket_fd			_listenSocket;

	// default initialization
	GatewayFactory		_gatewayFactory;
	RequestFactory		_requestFactory;
	RequestValidator	_requestValidator;
	Logger				*_logger;

	void	closeConnection(Connection &connection);

public:
	Server(ServerConfiguration const &config);

	socket_fd	getListenSocket() const;

	void		startListening(Error *error);
	void		handleConnection(Connection &clientConnection);
};

#endif
