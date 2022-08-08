#include "Error.hpp"

Error::Error(
	std::string const &message) :
	_message(message)
{

}

Error::Error(
	ResponseCode responseCode) :
	_responseCode(responseCode)
{

}

Error::Error(
	ResponseCode responseCode,
	std::string const &message) :
	_responseCode(responseCode),
	_message(message)
{

}

ResponseCode	Error::getResponseCode() const { return _responseCode; }
std::string		const &Error::getMessage() const { return _message; }
