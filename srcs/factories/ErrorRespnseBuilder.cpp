#include "ErrorResponseBuilder.hpp"
#include "ErrorPageGenerator.hpp"
#include "File.hpp"

ErrorResponseBuilder::ErrorResponseBuilder(
	ServerConfiguration const &config) :
	_config(config)
{

}

ErrorResponseBuilder::~ErrorResponseBuilder()
{

}

Response	*ErrorResponseBuilder::genereateAutomatically(Error const *error)
{
	ErrorPageGenerator errorPageGenerator;
	std::string body = errorPageGenerator.generate(error);

	return new Response(
		error->getResponseCode(),
		std::map<std::string, std::string>(),
		body
	);
}

Response				*ErrorResponseBuilder::build(Error const *error)
{
	ResponseCode responseCode = error->getResponseCode();

	if (_config.errorPagesMap.count(responseCode) != 1)
	{
		return genereateAutomatically(error);
	}

	std::string pathToErrorPage = _config.errorPagesMap.at(responseCode);
	File file(pathToErrorPage);

	std::string body;
	FileOperationResult readResult = file.readFile(body);
	if (readResult == Success)
	{
		return new Response(
			responseCode,
			std::map<std::string, std::string>(),
			body);
	}

	return genereateAutomatically(error);
}
