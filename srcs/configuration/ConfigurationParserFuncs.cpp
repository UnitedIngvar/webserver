#include "ConfigurationParser.hpp"
#include <iostream>
#include <fstream>
void ConfigurationParser::parseWorkerProcesses(const std::string &line, size_t &offset, std::string &error)
{
	int threadPoolSize = atoi(line.c_str());
	if (threadPoolSize == 0)
	{
		error = "wrong worker processes line";
		return;
	}
	this->configuration.threadPoolSize = threadPoolSize;
}

void ConfigurationParser::parseListen(const std::string &line, size_t &offset, std::string &error)
{
	int listen = atoi(line.c_str());
	if (listen == 0)
	{
		error = "wrong server->listen line";
		return;
	}
	this->configuration.ServerConfigurations->port = listen;
}

void ConfigurationParser::parseServerName(const std::string &line, size_t &offset, std::string &error)
{
	int left_i_saver, i = 0;

	while (line[i] && line[i] != ';')
	{
		left_i_saver = i;
		while (line[i] && line[i] != ' ' && line[i] != ';')
		{
			i++;
		}
		// может добавить валидацию на УРЛ
		this->configuration.ServerConfigurations->serverNames.push_back(line.substr(left_i_saver, i - left_i_saver));
	}
}

void ConfigurationParser::parseRoot(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseErrorPagesMap(const std::string &lines, size_t &offset, std::string &error)
{
	size_t offset_saver;
	while (lines[offset] && lines[offset] != '}')
	{
		while (!isdigit(lines[offset]))
		{
			offset++;
		}
		offset_saver = offset;
		while(lines[offset] != ' ')
		{
			offset++;
		}
		int errorCode = atoi(lines.substr(offset_saver, offset).c_str());
		offset_saver = offset;
		while (lines[offset] != '\n')
		{
			offset++;
		}
		std::string pathToErrorPage = lines.substr(offset_saver, offset - 1);
		std::ifstream file;
		file.open(pathToErrorPage);
		if (!file)
		{
			// мб найти другой способ форматирования строки
			char buffer[50];
			snprintf(buffer, sizeof(buffer), "could not open file with error code %d. Path: %s", errorCode, pathToErrorPage);
			error = buffer;
			return;
		}
		// не доделано
	}
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
