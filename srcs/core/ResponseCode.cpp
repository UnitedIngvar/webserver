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
		break;
	case BadRequest:
		return buildRepresentation("400", "Bad Request");
		break;
	case NotImplemented:
		return buildRepresentation("501", "Not Implemented");
		break;
	case HTTPVersionNotSupported:
		return buildRepresentation("505", "HTTP Version Not Supported");
		break;
	}
}

