#include "RequestValidator.hpp"
#include "ResponseCode.hpp"

bool	RequestValidator::requiredFieldIsEmpty(Request const *request)
{
	return
		request->getHttpVersion().length() == 0 ||
		request->getUrl().getFullUrl().length() == 0 ||
		request->getUrl().getPath().length() == 0;
}

bool	RequestValidator::validateRequest(Request const *request, ResponseCode &errorCode)
{
	if (request == nullptr)
	{
		errorCode = BadRequest;
		return false;
	}

	if (requiredFieldIsEmpty(request))
	{
		errorCode = BadRequest;
		return false;
	}

	if (request->getMethod() == INVALID)
	{
		errorCode = NotImplemented;
		return false;
	}

	if (request->getHeaders().count("Host") != 1)
	{
		errorCode = BadRequest;
		return false;
	}

	if (request->getHttpVersion().compare("HTTP/1.1") != 0)
	{
		errorCode = HTTPVersionNotSupported;
		return false;
	}

	return true;
}
