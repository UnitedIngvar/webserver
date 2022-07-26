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

std::string const	&RequestFactory::decodeUrl(std::string const &url)
{
	std::string decodedUrl;

	for (std::string::const_iterator iter = url.begin(), nd = url.end(); iter < nd; ++iter)
	{
		auto currentChar = *iter;

		switch(currentChar)
		{
			case '%':
				if (iter[1] && iter[2])
				{
					char hex[]{ iter[1], iter[2] };
					decodedUrl += static_cast<char>(strtol(hex, nullptr, 16));
					iter += 2;
				}
				break;
			case '+':
				decodedUrl += ' ';
				break;
			default:
				decodedUrl += currentChar;
		}
	}

	return decodedUrl;
}

Url					*RequestFactory::parseUrl(std::string const &url)
{
	if (url.length() == 0)
	{
		return new Url(
			"/",
			"/",
			"",
			"");
	}

	std::string	decodedUrl = decodeUrl(url);
	std::string	path;
	std::string	query;
	std::string	cgiExtension;

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

	return new Url(
		decodedUrl,
		path,
		query,
		cgiExtension
	);
}

Request				*RequestFactory::create(std::string const &request)
{
	int offset = 0;

	/* Pasrse the first line (Request line) */
	RequestMethod	method;
	std::string		url;
	std::string		httpVersion;

	std::string methodString = getStringTillSymbol(request, offset, ' ');
	method = mapRequestMethod(methodString);
	url = getStringTillSymbol(request, offset, ' ');
	httpVersion = getStringTillSymbol(request, offset, '\r\n');

	/* Parse the url*/
	Url *urlModel = parseUrl(url);

	/* Parse header fields */
	std::map<std::string, std::string> headers;
	while(true)
	{
		std::string headerName = getStringTillSymbol(request, offset, ':');
		std::string headerValue = getStringTillSymbol(request, offset, '\r\n');
		headers.insert(std::pair<std::string, std::string>(headerName, headerValue));
	}

	/* Parse the body*/
	offset++;
	std::string body = getStringTillSymbol(request, offset, '\0');

	return new Request(
		method,
		headers,
		url,
		httpVersion,
		body
	);
}
