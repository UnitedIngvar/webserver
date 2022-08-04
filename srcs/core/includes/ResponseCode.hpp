#ifndef RESPONSECODE_HPP
# define RESPONSECODE_HPP

# include <string>

// todo: заглушка на будущее

typedef enum ResponseCode
{
	OK = 200,
	BadRequest = 400,
	PageNotFound = 404,
	InternalServiceError = 500,

	UknownCode = -1,
} ResponseCode;

typedef struct ResponseCodeRepresentation
{
	std::string number;
	std::string phrase;
} ResponseCodeRepresentation;

ResponseCodeRepresentation	getCodeRepresentation(ResponseCode code);
ResponseCode				getErrorCodeFromInteger (int code);

#endif
