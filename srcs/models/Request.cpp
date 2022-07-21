#include "Request.hpp"

Request::Request(RequestMethod method,
	std::map<std::string, std::string> generalHeaders,
	std::map<std::string, std::string> responseHeaders,
	std::map<std::string, std::string> entityHeaders,
	std::string const &path,
	std::string const &messageBody,
	bool isCgi) :
	_generalHeaders(generalHeaders),
	_responseHeaders(responseHeaders),
	_entityHeaders(entityHeaders),
	_path(path),
	_messageBody(messageBody),
	_isCgi(isCgi)
{

}

Request::~Request()
{

}

RequestMethod						Request::getMethod() const { return _method; }
std::map<std::string, std::string>	Request::getGeneralHeaders() const { return _generalHeaders; }
std::map<std::string, std::string>	Request::getResponseHeaders() const { return _responseHeaders; }
std::map<std::string, std::string>	Request::getEntityHeaders() const { return _entityHeaders; }
std::string							Request::getPath() const { return _path; }
std::string							Request::getMessageBody() const { return _messageBody; }
bool								Request::getIsCgi() const { return _isCgi; }
