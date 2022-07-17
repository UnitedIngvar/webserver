#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "ResponseCode.hpp"
# include <map>

class Response
{
private:
	ResponseCode						_responseCode;
	std::map<std::string, std::string>	_generalHeaders;
	std::map<std::string, std::string>	_responseHeaders;
	std::map<std::string, std::string>	_entityHeaders;
	std::string							_body;

	std::string							mapToHeaderFormatString(std::map<std::string, std::string> map) const;

// TODO: возможно, хедеры можно будет сделать просто массивами строк
public:
	Response(
		ResponseCode						responseCode,
		std::map<std::string, std::string>	generalHeaders,
		std::map<std::string, std::string>	responseHeaders,
		std::map<std::string, std::string>	entityHeaders,
		std::string	const					&body);
	~Response();

	// TODO: не уверен, что понадобятся, возможно дропнем потом
	ResponseCode						getResponseCode() const;

	std::string							toResponseString() const;
};

#endif
