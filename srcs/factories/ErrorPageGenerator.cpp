#include "ErrorPageGenerator.hpp"

ErrorPageGenerator::ErrorPageGenerator()
{

}

ErrorPageGenerator::~ErrorPageGenerator()
{

}

std::string	ErrorPageGenerator::generate(Error const *error) const
{
	ResponseCodeRepresentation representanion = getCodeRepresentation(error->getResponseCode());

	std::string errorPage =
	"<!DOCTYPE html>\n\
	<html>\n\
	<body\n\
	<h1>Error " + representanion.number + "(" + representanion.phrase + ")</h1>\n\
	<p>Error message: " + error->getMessage() + " </p>\n\
	</body>\n\
	</html>";

	return errorPage;
}
