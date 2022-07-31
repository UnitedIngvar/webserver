#include "ConfigurationParser.hpp"
#include "File.hpp"

ConfigurationParser::ConfigurationParser()
{

}

ConfigurationParser::~ConfigurationParser()
{

}



Configuration ConfigurationParser::parseConfig(std::string pathToFile)
{
	File file(pathToFile);
	std::string fileContents;
	Configuration Configuration;

	FileOperationResult readResult = file.readFile(fileContents);
	if (readResult != Success)
	{
		throw new FileReadException(pathToFile);
	}


}

const char	*ConfigurationParser::FileReadException::what() const throw()
{
	std::string errorMessage =
		"error while reading a file. File path: " + _filePath + "\n";

	return errorMessage.c_str();
}

const char	*ConfigurationParser::ConfigurationFormatError::what() const throw()
{
	return "Configuration file has invalid format";
}
