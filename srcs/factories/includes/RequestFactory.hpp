#ifndef REQUESTFACTORY_HPP
# define REQUESTFACTORY_HPP

# include <string>
# include <map>
# include "Request.hpp"

class RequestFactory
{
private:
	bool								checkPrerequisits(std::string const &request);
	Request								*createInvalidRequestModel();
	RequestMethod						mapRequestMethod(std::string const &methodString);
	std::string							getStringTillChars(std::string const &request, size_t &offset, std::string const &chars);
	std::string							decodeUrl(std::string const &url);
	Url									*parseUrl(std::string const &url);
	std::map<std::string, std::string>	parseHeaders(std::string const &request, size_t &offset);

public:
	Request				*create(std::string const &requestString);
};

#endif
