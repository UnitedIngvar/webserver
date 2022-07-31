#include "Request.hpp"

Request::Request(
		RequestMethod						method,
		std::map<std::string, std::string>	headers,
		Url								 	&url,
		std::string							const &httpVersion,
		std::string							const &messageBody) :
	_method(method),
	_headers(headers),
	_url(url),
	_httpVersion(httpVersion),
	_messageBody(messageBody)
{

}

Request::~Request()
{
	delete &_url;
}

RequestMethod							Request::getMethod() const { return _method; }
std::map<std::string, std::string>		const &Request::getHeaders() const { return _headers; }
std::string								const &Request::getMessageBody() const { return _messageBody; }
std::string								const &Request::getHttpVersion() const { return _httpVersion; }
Url										const &Request::getUrl() const { return _url; }
