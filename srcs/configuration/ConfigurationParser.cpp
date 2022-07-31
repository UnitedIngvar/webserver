#include "ConfigurationParser.hpp"
#include "File.hpp"

ConfigurationParser::ConfigurationParser()
{
	_arrayOfParseFuncs = new configParserFunc[15];
	_arrayOfParseFuncsNames = new std::string[15];
	_arrayOfParseFuncs[0] = &ConfigurationParser::parseListen;
	_arrayOfParseFuncsNames[0] = "listen";
	_arrayOfParseFuncs[1] = &ConfigurationParser::parseListen;
	_arrayOfParseFuncsNames[1] = "serverName";
	_arrayOfParseFuncs[2] = &ConfigurationParser::parseServerName;
	_arrayOfParseFuncsNames[2] = "root";
	_arrayOfParseFuncs[3] = &ConfigurationParser::parseRoot;
	_arrayOfParseFuncsNames[3] = "errorPagesMap";
	_arrayOfParseFuncs[3] = &ConfigurationParser::parseErrorPagesMap;
	_arrayOfParseFuncsNames[4] = "redirection";
	_arrayOfParseFuncs[4] = &ConfigurationParser::parseRedirection;
	_arrayOfParseFuncsNames[5] = "maxBodySize";
	_arrayOfParseFuncs[5] = &ConfigurationParser::parseMaxBodySize;
	_arrayOfParseFuncsNames[6] = "location";
	_arrayOfParseFuncs[6] = &ConfigurationParser::parseLocation;
	_arrayOfParseFuncsNames[7] = "methods";
	_arrayOfParseFuncs[7] = &ConfigurationParser::parseMethods;
	_arrayOfParseFuncsNames[8] = "directory";
	_arrayOfParseFuncs[8] = &ConfigurationParser::parseDirectory;
	_arrayOfParseFuncsNames[9] = "indexFile";
	_arrayOfParseFuncs[9] = &ConfigurationParser::parseIndexFile;
	_arrayOfParseFuncsNames[10] = "cgiExtension";
	_arrayOfParseFuncs[10] = &ConfigurationParser::parseCgiExtension;
	_arrayOfParseFuncsNames[11] = "dirListOn";
	_arrayOfParseFuncs[11] = &ConfigurationParser::parseDirListOn;
	_arrayOfParseFuncsNames[12] = "workerProcesses";
	_arrayOfParseFuncs[12] = &ConfigurationParser::parseWorkerProcesses;
	// _arrayOfParseFuncsNames[0] = "listen";
	// _arrayOfParseFuncs[0] = &ConfigurationParser::parseListen;
	// _arrayOfParseFuncsNames[0] = "listen";
	ServerConfiguration serverConfiguration;
	configuration.ServerConfigurations = &serverConfiguration;
}

ConfigurationParser::~ConfigurationParser()
{
	delete[] _arrayOfParseFuncs;
	delete[] _arrayOfParseFuncsNames;
}



Configuration ConfigurationParser::parseConfig(std::string pathToFile)
{
	File file(pathToFile);
	std::string fileContents;

	FileOperationResult readResult = file.readFile(fileContents);
	if (readResult != Success)
	{
		throw new FileReadException(pathToFile);
	}

	size_t i = 0;
	size_t left_i_saver;
	std::string error;
	while (fileContents[i])
	{
		left_i_saver = i;
		while (fileContents[i] != ';' && fileContents[i] != '{')
		{
			i++;
		}
		if (fileContents[i] == '{')
		{

		}
		parseConfigLine(fileContents.substr(left_i_saver, i - left_i_saver), i, error);
		if (error != "")
		{
			throw new ConfigurationFormatError;
		}
		i++;
	}
}

void ConfigurationParser::parseConfigLine(const std::string &line, size_t &offset, std::string &error)
{
	int i = 0;
	while (line[i] != ' ')
	{
		i++;
	}
	std::string name = line.substr(0, i - 1);
	std::string lineAfterName = line.substr(i - 1, line.length() - i);
	offset += i;
	i = 0;
	while (i != 15)
	{
		if (_arrayOfParseFuncsNames[i].compare(name) == 0)
		{
			(this->*_arrayOfParseFuncs[i])(lineAfterName, offset, error);
			if (error != "")
			{
				return ;
			}
		}
	}
	offset += i;
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
