#ifndef RESPONSEBUILDER_HPP
# define RESPONSEBUILDER_HPP

# include "Response.hpp"
# include "Configuration.hpp"

// TODO: build response factory
class ResponseFactory
{
private:
	ServerConfiguration _config;

public:
	ResponseFactory(ServerConfiguration config);
	~ResponseFactory();

};


#endif
