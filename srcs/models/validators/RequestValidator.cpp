#include "RequestValidator.hpp"
#include "ResponseCode.hpp"

bool	RequestValidator::requiredFieldIsEmpty(Request const *request)
{
	return
		request->getHttpVersion().length() == 0 ||
		request->getUrl().getFullUrl().length() == 0 ||
		request->getUrl().getPath().length() == 0;
}

bool	RequestValidator::validateRequest(Request const *request, Error *error)
{
	if (request == nullptr)
	{
		error = new Error(BadRequest);
		return false;
	}

	if (requiredFieldIsEmpty(request))
	{
		error = new Error(BadRequest);
		return false;
	}

	if (request->getMethod() == INVALID)
	{
		error = new Error(NotImplemented);
		return false;
	}

	if (request->getHeaders().count("Host") != 1)
	{
		error = new Error(BadRequest);
		return false;
	}

	if (request->getHttpVersion().compare("HTTP/1.1") != 0)
	{
		error = new Error(HTTPVersionNotSupported);
		return false;
	}

	return true;
}
