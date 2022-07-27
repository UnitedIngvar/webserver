#ifndef REQUESTFACTORY_HPP
# define REQUESTFACTORY_HPP

# include <string>
# include <map>
# include "Request.hpp"

class RequestFactory
{
private:
	RequestMethod		mapRequestMethod(std::string const &methodString);
	std::string			getStringTillChars(std::string const &request, int &offset, std::string const &chars);
	std::string			decodeUrl(std::string const &url);
	Url					*parseUrl(std::string const &url);

public:
	Request				*create(std::string const &requestString);
};

#endif
