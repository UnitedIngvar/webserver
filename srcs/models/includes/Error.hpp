#ifndef ERROR_HPP
# define  ERROR_HPP

#include "ResponseCode.hpp"

class Error
{
private:
	ResponseCode	_responseCode;
	std::string		_message;

public:
	Error(
		ResponseCode responseCode,
		std::string const &message);

	Error(
		std::string const &message);

	ResponseCode	getResponseCode() const;
	std::string		const &getMessage() const;
};

#endif
