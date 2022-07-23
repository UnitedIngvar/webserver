#ifndef REQUESTFACTORY_HPP
# define REQUESTFACTORY_HPP

# include <string>
# include <map>
# include "Request.hpp"

class RequestFactory
{
private:
	//static std::map<std::string, RequestMethod> _requestMethodMap;
	static RequestMethod		mapRequestMethod(std::string const &methodString);
	static std::string const	&getStringTillSymbol(std::string const &request, int &offset, char symbol);

public:
	static Request				&create(std::string const &requestString);
};

#endif
