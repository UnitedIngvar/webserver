#include "ConfigurationParser.hpp"

void ConfigurationParser::parseWorkerProcesses(const std::string &line, size_t &offset, std::string &error)
{
	int i = 0;

	// TODO: вывести в отдельную функцию как у Игоря
	while (line[i] && line[i] != ';')
	{
		i++;
	}


}

void ConfigurationParser::parseListen(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseServerName(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseRoot(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseErrorPagesMap(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseRedirection(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseMaxBodySize(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseLocation(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseMethods(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseDirectory(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseIndexFile(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseCgiExtension(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseDirListOn(const std::string &line, size_t &offset, std::string &error)
{

}
