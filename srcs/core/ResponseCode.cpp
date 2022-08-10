#include "ResponseCode.hpp"

static ResponseCodeRepresentation buildRepresentation(std::string const &number, std::string const &phrase)
{
	ResponseCodeRepresentation representation;

	representation.number = number;
	representation.phrase = phrase;
	return representation;
}

ResponseCodeRepresentation	getCodeRepresentation(ResponseCode code)
{
	switch (code)
	{
	case OK:
		return buildRepresentation("200", "OK");
	case BadRequest:
		return buildRepresentation("400", "Bad Request");
	case NotFound:
		return buildRepresentation("404", "Not Found");
	case NotImplemented:
		return buildRepresentation("501", "Not Implemented");
	case HTTPVersionNotSupported:
		return buildRepresentation("505", "HTTP Version Not Supported");
	default:
		return buildRepresentation("-1", "Response code not found");
	}
}