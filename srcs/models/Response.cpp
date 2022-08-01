#include "Response.hpp"

Response::Response(
	ResponseCode responseCode,
	std::map<std::string, std::string> generalHeaders,
	std::map<std::string, std::string> responseHeaders,
	std::map<std::string, std::string> entityHeaders,
	std::string const &body) :
	_responseCode(responseCode),
	_generalHeaders(generalHeaders),
	_responseHeaders(responseHeaders),
	_entityHeaders(entityHeaders),
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

	std::string headers = mapToHeaderFormatString(_generalHeaders)
		.append(mapToHeaderFormatString(_responseHeaders))
		.append(mapToHeaderFormatString(_entityHeaders));

	return statusLine + headers + "\n" + _body;
}

std::string		Response::mapToHeaderFormatString(std::map<std::string, std::string> map) const
{
	std::string result;
	for (std::map<std::string, std::string>::iterator it = map.begin(); it != map.end(); it++)
	{
		result.append(it->first);
		result.append(": ");
		result.append(it->second);
		result.append("\n");
	}

	return result;
}
