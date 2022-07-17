#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>
# include <map>
# include "RequestMethod.hpp"

class Request
{
private:
	RequestMethod						_method;
	std::map<std::string, std::string>	_generalHeaders;
	std::map<std::string, std::string>	_responseHeaders;
	std::map<std::string, std::string>	_entityHeaders;
	std::string							_path;
	std::string							_messageBody;
	bool								_isCgi;

public:
	Request(RequestMethod					method,
		std::map<std::string, std::string>	generalHeaders,
		std::map<std::string, std::string>	responseHeaders,
		std::map<std::string, std::string>	entityHeaders,
		std::string	const					&path,
		std::string	const					&messageBody,
		bool								isCgi);
	~Request();

	RequestMethod						getMethod() const;
	std::map<std::string, std::string>	getGeneralHeaders() const;
	std::map<std::string, std::string>	getResponseHeaders() const;
	std::map<std::string, std::string>	getEntityHeaders() const;
	std::string							getPath() const;
	std::string							getMessageBody() const;
	bool								getIsCgi() const;
};

#endif
