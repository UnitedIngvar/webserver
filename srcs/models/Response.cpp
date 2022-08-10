#include "Response.hpp"

Response::Response(
	ResponseCode responseCode,
	std::map<std::string, std::string> headers,
	std::string const &body) :
	_responseCode(responseCode),
	_headers(headers),
	_body(body)
{

}

Response::~Response()
{

}

ResponseCode	Response::getResponseCode() const { return _responseCode; }

std::string		Response::toResponseString() const
{
	ResponseCodeRepresentation codeRepresentation = getCodeRepresentation(_responseCode);

	std::string statusLine =
		"HTTP/1.1 " + // todo: вбил гвоздем версию, возможно придется ее тоже динамически проставлять
		codeRepresentation.number +
		" " +
		codeRepresentation.phrase
		+ "\n";

	std::string headers = mapToHeaderFormatString(_headers);

	return statusLine + headers + "\n" + _body;
}

std::string		Response::mapToHeaderFormatString(std::map<std::string, std::string> map) const
{
	std::string result = "";
	for (std::map<std::string, std::string>::iterator it = map.begin(); it != map.end(); it++)
	{
		result.append(it->first);
		result.append(": ");
		result.append(it->second);
		result.append("\n");
	}

	return result;
}
