#include "RequestFactory.hpp"
#include <iostream>

std::string		RequestFactory::getStringTillChars(
	std::string const &request, int &offset, std::string const &chars)
{
	int symbolPosition = request.find(chars, offset);
	std::string stringTillSymbol = request.substr(offset, symbolPosition - offset);

	offset = symbolPosition + chars.length();

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

std::string		RequestFactory::decodeUrl(std::string const &url)
{
	std::string decodedUrl;

	for (std::string::const_iterator iter = url.begin(), nd = url.end(); iter < nd; ++iter)
	{
		char currentChar = *iter;

		switch(currentChar)
		{
			case '%':
				if (iter[1] && iter[2])
				{
					char hex[] = { iter[1], iter[2] };
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

Url				*RequestFactory::parseUrl(std::string const &url)
{
	if (url.length() == 0)
	{
		return new Url(
			"/",
			"/",
			"");
	}

	std::string	decodedUrl = decodeUrl(url);
	std::string	path;
	std::string	query;

	if (url.find('?') == std::string::npos)
	{
		path = decodedUrl;
	}
	else
	{
		int urlOffset = 0;
		path = getStringTillChars(url, urlOffset, "?");
		query = url.substr(urlOffset);
	}

	return new Url(
		decodedUrl,
		path,
		query);
}

Request			*RequestFactory::create(std::string const &request)
{
	int offset = 0;

	/* Pasrse the request line */
	RequestMethod	method;
	std::string		url;
	std::string		httpVersion;

	std::string methodString = getStringTillChars(request, offset, " ");
	method = mapRequestMethod(methodString);
	url = getStringTillChars(request, offset, " ");
	httpVersion = getStringTillChars(request, offset, "\r\n");

	/* Parse the url*/
	Url *urlModel = parseUrl(url);

	/* Parse header fields */
	std::map<std::string, std::string> headers;
	do
	{
		std::string headerName = getStringTillChars(request, offset, ":");
		offset++;
		std::string headerValue = getStringTillChars(request, offset, "\r\n");
		headers.insert(std::pair<std::string, std::string>(headerName, headerValue));
	} while (request.compare(offset, 2, "\r\n") != 0);

	/* Parse the body*/
	offset += 2;
	std::string body = request.substr(offset);

	return new Request(
		method,
		headers,
		*urlModel,
		httpVersion,
		body
	);
}
