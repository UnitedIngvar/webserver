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
	Url									&_url;
	std::string							_httpVersion;
	std::map<std::string, std::string>	_headers;
	std::string							_messageBody;
	bool								_isCgi;

public:
	Request(RequestMethod					method,
		std::map<std::string, std::string>	headers,
		Url									&url,
		std::string	const					&httpVersion,
		std::string	const					&messageBody,
		bool								isCgi);
	~Request();

	RequestMethod						getMethod() const;
	Url									const &getUrl() const;
	std::string	const					const &getHttpVersion() const;
	std::map<std::string, std::string>	const &getHeaders() const;
	std::string	const					const &getMessageBody() const;
	bool								isCgi() const;
};

#endif
