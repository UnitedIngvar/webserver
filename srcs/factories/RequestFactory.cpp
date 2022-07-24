#include "RequestFactory.hpp"

std::string const	&RequestFactory::getStringTillSymbol(
	std::string const &request, int &offset, char symbol)
{
	int symbolPosition = request.find(symbol, offset);
	std::string stringTillSymbol = request.substr(offset, symbolPosition - offset);

	offset = symbolPosition + 1;

	return stringTillSymbol;
}

RequestMethod	RequestFactory::mapRequestMethod(std::string const &methodString)
{
	if (methodString.compare("GET") == 0)
	{
		return GET;
	}
	else if (methodString.compare("POST") == 0)
	{
		return POST;
	}
	else if (methodString.compare("PUT") == 0)
	{
		return PUT;
	}
	else
	{
		return DELETE;
	}
}

Url					&RequestFactory::parseUrl(std::string const &url)
{
	if (url.find('?') == std::string::npos)
	{
		path = url;
	}
	else
	{
		int urlOffset = 0;
		path = getStringTillSymbol(url, urlOffset, '?');
		query = getStringTillSymbol(url, urlOffset, '\0');
	}
}

Request &RequestFactory::create(std::string const &request)
{
	int offset = 0;

	/* Pasrse the first line (Request line) */
	RequestMethod	method;
	std::string		url;
	std::string		httpVersion;

	 //не забыть, что может быть кодировка % HEX HEX в URI (уточнить про другие места).
	 // we should always replace  null abs_path with "/"
	 // Че делать с запросом к самому серверу '*'?
	std::string methodString = getStringTillSymbol(request, offset, ' ');
	method = mapRequestMethod(methodString);
	url = getStringTillSymbol(request, offset, ' ');
	httpVersion = getStringTillSymbol(request, offset, '\r\n');

	/* Parse the url, search for query string */
	if (url.find('?') == std::string::npos)
	{
		path = url;
	}
	else
	{
		int urlOffset = 0;
		path = getStringTillSymbol(url, urlOffset, '?');
		query = getStringTillSymbol(url, urlOffset, '\0');
	}

	/* Parse header fields */
	std::map<std::string, std::string> headers;
	while(true)
	{
		std::string headerName = getStringTillSymbol(request, offset, ':');
		std::string headerValue = getStringTillSymbol(request, offset, '\r\n');
		headers.insert(std::pair<std::string, std::string>(headerName, headerValue));
	}

	/* Parse the body, if there is one */
	std::string body;
	if (offset >= request.length() - 1)
	{
		/* skip the CRLF inbetween the header fields and body */
		offset++;

		body = getStringTillSymbol(request, offset, '\0');
	}

	Request *reqeust()
}
