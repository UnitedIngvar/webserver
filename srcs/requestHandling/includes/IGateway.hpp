#ifndef IGATEWAY_HPP
# define IGATEWAY_HPP

# include "Request.hpp"
# include "Response.hpp"
# include "Error.hpp"

class IGateway
{
public:
	virtual Response	*processRequest(Request const *request, Error const *err) const = 0;
};

#endif
