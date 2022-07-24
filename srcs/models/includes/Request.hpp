#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>
# include <map>
# include "RequestMethod.hpp"
# include "Url.hpp"

class Request
{
private:
	RequestMethod						_method;
	Url									_url;
	std::string							_httpVersion;
	std::map<std::string, std::string>	_headers;
	std::string							_messageBody;
	bool								_isCgi;

public:
	Request(RequestMethod					method,
		std::map<std::string, std::string>	headers,
		Url									url,
		std::string	const					&httpVersion,
		std::string	const					&messageBody,
		bool								isCgi);
	~Request();

	RequestMethod						getMethod() const;
	Url									getUrl() const;
	std::string							getHttpVersion() const;
	std::map<std::string, std::string>	getHeaders() const;
	std::string							getMessageBody() const;
	bool								getIsCgi() const;
};

#endif
