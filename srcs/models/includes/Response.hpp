#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "ResponseCode.hpp"
# include <map>

class Response
{
private:
	ResponseCode						_responseCode;
	std::map<std::string, std::string>	_headers;
	std::string							_body;

	std::string							mapToHeaderFormatString(std::map<std::string, std::string> map) const;

// TODO: возможно, хедеры можно будет сделать просто массивами строк
public:
	Response(
		ResponseCode						responseCode,
		std::map<std::string, std::string>	headers,
		std::string	const					&body);
	~Response();

	// TODO: не уверен, что понадобятся, возможно дропнем потом
	ResponseCode						getResponseCode() const;

	std::string							toResponseString() const;
};

#endif
