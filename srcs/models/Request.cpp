#include "Request.hpp"

Request::Request(
		RequestMethod						method,
		std::map<std::string, std::string>	headers,
		Url									*url,
		std::string	const					&httpVersion,
		std::string	const					&messageBody,
		bool								isCgi) :
	_method(method),
	_headers(headers),
	_url(url),
	_httpVersion(httpVersion),
	_messageBody(messageBody),
	_isCgi(isCgi)
{

}

Request::~Request()
{

}

RequestMethod						Request::getMethod() const { return _method; }
std::map<std::string, std::string>	Request::getHeaders() const { return _headers; }
std::string							Request::getUrl() const { return _url; }
std::string							Request::getMessageBody() const { return _messageBody; }
bool								Request::getIsCgi() const { return _isCgi; }
