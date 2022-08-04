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
		return buildRepresentation("400", "BadRequest");;
		break;
	case PageNotFound:
		return buildRepresentation("404", "NotFound");
	default:
		return buildRepresentation("-1", "Uknown response code");
	}
}

ResponseCode getErrorCodeFromInteger (int code)
{
	switch (code)
	{
		case 200:
			return OK;
		case 400:
			return BadRequest;
		case 404:
			return PageNotFound;
		case 500:
			return InternalServiceError;
		default:
			return UknownCode;
	}
}
