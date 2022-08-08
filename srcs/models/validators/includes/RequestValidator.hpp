#ifndef REQUESTVALIDATOR_HPP
# define REQUESTVALIDATOR_HPP

# include "Request.hpp"
# include "Error.hpp"

class RequestValidator
{
private:
	bool	requiredFieldIsEmpty(Request const *request);

public:
	bool	validateRequest(Request const *request, Error *error);
};

#endif
