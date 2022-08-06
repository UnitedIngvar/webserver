#ifndef SERVER_HPP
# define SERVER_HPP

# include "Configuration.hpp"
# include "GatewayFactory.hpp"
# include "RequestValidator.hpp"
# include "RequestFactory.hpp"
# include "Logger.hpp"
# include "Core.hpp"

class Server
{
private:
	// initialized dynamicaly
	ServerConfiguration	_config;
	socket_fd			_listenSocket;

	// default initialization
	GatewayFactory		_gatewayFactory;
	RequestFactory		_requestFactory;
	ReuqestValidator	_requestValidator;

public:
	Server(ServerConfiguration const &config);

	socket_fd	getListenSocket() const;

	void		startListening(Error *error);
	void		handleConnection(socket_fd clientConnection);
};

#endif
