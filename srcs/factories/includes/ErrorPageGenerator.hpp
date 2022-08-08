#ifndef ERROR_PAGE_GENERATOR_HPP
# define ERROR_PAGE_GENERATOR_HPP

# include <string>
# include "Error.hpp"
# include "ResponseCode.hpp"

class ErrorPageGenerator
{
public:
	ErrorPageGenerator();
	~ErrorPageGenerator();

	std::string	generate(Error const *error) const;
};

#endif
