#ifndef ERROR_RESPONSE_BUILDER_HPP
# define ERROR_RESPONSE_BUILDER_HPP

# include "Configuration.hpp"
# include "Response.hpp"
# include "Error.hpp"
# include <map>

class ErrorResponseBuilder
{
private:
	ServerConfiguration const &_config;

	Response	*genereateAutomatically(Error const *error);

public:
	ErrorResponseBuilder(ServerConfiguration const &config);
	~ErrorResponseBuilder();

	Response	*build(Error const *error);
};

#endif
