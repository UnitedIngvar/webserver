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

	default:
		break;
	}
}
