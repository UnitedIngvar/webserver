#include "RequestFactory.hpp"
#include <iostream>

std::string		RequestFactory::getStringTillChars(
	std::string const &request, size_t &offset, std::string const &chars)
{
	size_t symbolPosition = request.find(chars, offset);

	if (symbolPosition == std::string::npos)
	{
		return "";
	}

	std::string stringTillSymbol = request.substr(offset, symbolPosition - offset);

	offset = symbolPosition + chars.length();

	return stringTillSymbol;
}

bool				RequestFactory::checkPrerequisits(std::string const &request)
{
	size_t offset = 0;

	int crlfCount = 0;
	const std::string crlf = "\r\n";
	for (size_t i = 0; i < request.length(); i++)
	{
		size_t crlfPosition = request.find(crlf, offset);
		if (crlfPosition == std::string::npos)
		{
			break;
		}

		offset = crlfPosition + crlf.length();
		crlfCount++;
	}

	return crlfCount >= 3;
}

// todo: временное решение. В будущем нужно придумать что-то получше.
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
	else if (methodString.compare("DELETE") == 0)
	{
		return DELETE;
	}
	else
	{
		return INVALID;
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
		size_t urlOffset = 0;
		path = getStringTillChars(decodedUrl, urlOffset, "?");
		query = decodedUrl.substr(urlOffset);
	}

	return new Url(
		decodedUrl,
		path,
		query);
}

std::map<std::string, std::string>	RequestFactory::parseHeaders(std::string const &request, size_t &offset)
{
	std::map<std::string, std::string> headers;
	size_t lengthTillCRLF = offset - request.find("\r\n", offset);
	if (lengthTillCRLF != 0)
	{
		do
		{
			std::string headerName = getStringTillChars(request, offset, ":");
			offset++;
			std::string headerValue = getStringTillChars(request, offset, "\r\n");
			headers.insert(std::pair<std::string, std::string>(headerName, headerValue));
		} while (request.compare(offset, 2, "\r\n") != 0);
	}
	else
	{
		offset += 2;
	}

	return headers;
}

Request				*RequestFactory::createInvalidRequestModel()
{
	Url *urlModel = new Url("", "", "");
	return new Request(
		INVALID,
		std::map<std::string, std::string>(),
		*urlModel,
		"",
		"");
}

Request			*RequestFactory::create(std::string const &request)
{
	size_t offset = 0;

	if (checkPrerequisits(request) == false)
	{
		Request *request = createInvalidRequestModel();
		return request;
	}

	/* Pasrse the request line */
	RequestMethod	method;
	std::string		url;
	std::string		httpVersion;

	std::string methodString = getStringTillChars(request, offset, " ");
	method = mapRequestMethod(methodString);
	url = getStringTillChars(request, offset, " ");
	httpVersion = getStringTillChars(request, offset, "\r\n");
	Url *urlModel = parseUrl(url);

	/* Parse header fields */
	std::map<std::string, std::string> headers = parseHeaders(request, offset);

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
