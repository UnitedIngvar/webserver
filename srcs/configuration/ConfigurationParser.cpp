#include "ConfigurationParser.hpp"
#include "File.hpp"

ConfigurationParser::ConfigurationParser()
{
	_arrayOfParseServerFuncs = new configParserFunc[7];
	_arrayOfParseServerFuncsNames = new std::string[7];

	_arrayOfParseServerFuncs[0] = &ConfigurationParser::parseListen;
	_arrayOfParseServerFuncsNames[0] = "listen";
	_arrayOfParseServerFuncs[1] = &ConfigurationParser::parseListen;
	_arrayOfParseServerFuncsNames[1] = "serverName";
	_arrayOfParseServerFuncs[2] = &ConfigurationParser::parseServerName;
	_arrayOfParseServerFuncsNames[2] = "root";
	_arrayOfParseServerFuncs[3] = &ConfigurationParser::parseRoot;
	_arrayOfParseServerFuncsNames[3] = "errorPagesMap";
	_arrayOfParseServerFuncs[3] = &ConfigurationParser::parseErrorPagesMap;
	_arrayOfParseServerFuncsNames[4] = "redirection";
	_arrayOfParseServerFuncs[4] = &ConfigurationParser::parseRedirection;
	_arrayOfParseServerFuncsNames[5] = "maxBodySize";
	_arrayOfParseServerFuncs[5] = &ConfigurationParser::parseMaxBodySize;
	_arrayOfParseServerFuncsNames[6] = "location";

	_arrayOfParseLocationFuncs = new configParserFunc[6];
	_arrayOfParseLocationFuncsNames = new std::string[6];

	_arrayOfParseLocationFuncs[6] = &ConfigurationParser::parseLocation;
	_arrayOfParseLocationFuncsNames[7] = "methods";
	_arrayOfParseLocationFuncs[7] = &ConfigurationParser::parseMethods;
	_arrayOfParseLocationFuncsNames[8] = "directory";
	_arrayOfParseLocationFuncs[8] = &ConfigurationParser::parseDirectory;
	_arrayOfParseLocationFuncsNames[9] = "indexFile";
	_arrayOfParseLocationFuncs[9] = &ConfigurationParser::parseIndexFile;
	_arrayOfParseLocationFuncsNames[10] = "cgiExtension";
	_arrayOfParseLocationFuncs[10] = &ConfigurationParser::parseCgiExtension;
	_arrayOfParseLocationFuncsNames[11] = "dirListOn";
	_arrayOfParseLocationFuncs[11] = &ConfigurationParser::parseDirListOn;

	ServerConfiguration serverConfiguration;
	configuration.ServerConfigurations = &serverConfiguration;
}

ConfigurationParser::~ConfigurationParser()
{
	delete[] _arrayOfParseServerFuncs;
	delete[] _arrayOfParseServerFuncsNames;
	delete[] _arrayOfParseLocationFuncs;
	delete[] _arrayOfParseLocationFuncsNames;
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
		while (fileContents[i] && fileContents[i] != ';' && fileContents[i] != '{' && fileContents[i] != '\n')
		{
			i++;
		}
		switch (fileContents[i])
		{
			case '\0':
				return;
			case '\n':
				continue;
			case '{':
				parseEmbeddedLine(fileContents, i, error);
				return;
			case ';':
				parseConfigLine(fileContents.substr(left_i_saver, i - left_i_saver), i, error);
				if (error != "")
				{
					throw new ConfigurationFormatError;
				}
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
	if (name.compare("workerProcesses") == 0)
	{
		parseWorkerProcesses(lineAfterName, offset, error);
		return ;
	}
	while (i != 7)
	{
		if (_arrayOfParseServerFuncsNames[i].compare(name) == 0)
		{
			(this->*_arrayOfParseServerFuncs[i])(lineAfterName, offset, error);
			if (error != "")
			{
				return ;
			}
		}
	}
	offset += i;
}

void ConfigurationParser::parseEmbeddedLine(const std::string &lines, size_t &offset, std::string &error)
{
	while (lines[offset])
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
