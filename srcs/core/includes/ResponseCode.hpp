#ifndef RESPONSECODE_HPP
# define RESPONSECODE_HPP

# include <string>

// todo: заглушка на будущее

typedef enum ResponseCode
{
	OK = 200,
	BadRequest = 400
} ResponseCode;

typedef struct ResponseCodeRepresentation
{
	std::string number;
	std::string phrase;
} ResponseCodeRepresentation;

ResponseCodeRepresentation	getCodeRepresentation(ResponseCode code);
#endif
