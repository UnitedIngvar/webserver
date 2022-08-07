/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftassada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 03:10:49 by ftassada          #+#    #+#             */
/*   Updated: 2022/08/05 15:26:15 by ftassada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigurationParser.hpp"
#include "File.hpp"

ConfigurationParser::ConfigurationParser()
{
	_serverParseFuncs.insert(std::pair<std::string, configParserFunc>("listen", &ConfigurationParser::parseListen));
	_serverParseFuncs.insert(std::pair<std::string, configParserFunc>("serverName", &ConfigurationParser::parseServerName));
	_serverParseFuncs.insert(std::pair<std::string, configParserFunc>("root", &ConfigurationParser::parseRoot));
	_serverParseFuncs.insert(std::pair<std::string, configParserFunc>("errorPagesMap", &ConfigurationParser::parseErrorPagesMap));
	_serverParseFuncs.insert(std::pair<std::string, configParserFunc>("redirection", &ConfigurationParser::parseRedirection));
	_serverParseFuncs.insert(std::pair<std::string, configParserFunc>("maxBodySize", &ConfigurationParser::parseMaxBodySize));

	_locationParseFuncs.insert(std::pair<std::string, configParserFunc>("methods", &ConfigurationParser::parseMethods));
	_locationParseFuncs.insert(std::pair<std::string, configParserFunc>("directory", &ConfigurationParser::parseDirectory));
	_locationParseFuncs.insert(std::pair<std::string, configParserFunc>("indexFile", &ConfigurationParser::parseIndexFile));
	_locationParseFuncs.insert(std::pair<std::string, configParserFunc>("cgiExtension", &ConfigurationParser::parseCgiExtension));
	_locationParseFuncs.insert(std::pair<std::string, configParserFunc>("dirListOn", &ConfigurationParser::parseDirListOn));
}

Configuration ConfigurationParser::parseConfig(std::string pathToFile)
{
	File file(pathToFile);
	std::string fileContents;

	FileOperationResult readResult = file.readFile(fileContents);
	if (readResult != Success)
	{
		std::cerr << "could not open config file. Error: " + File::getResultStringFormat(readResult);
		return this->_configuration;
	}

	size_t i = 0;
	size_t left_i_saver;
	Error *error = nullptr;
	while (fileContents[i])
	{
		left_i_saver = i;
		while (fileContents[i] && fileContents[i] != ';' && fileContents[i] != '{' && fileContents[i] != '\n')
		{
			i++;
		}
		switch (fileContents[i])
		{
			case '\n':
				continue;
			case '{':
				parseEmbeddedLine(fileContents, left_i_saver, error);
				if (error != nullptr)
				{
					throw error->getMessage();
				}
				i = left_i_saver;
				break;
			case ';':
				parseConfigLine(fileContents.substr(left_i_saver, i - left_i_saver), i, error);
				if (error != nullptr)
				{
					throw "could not parse config line. error: " + error->getMessage();
				}
		}
		while (fileContents[i] && !isalnum(fileContents[i]))
		{
			i++;
		}
	}

	return this->_configuration;
}

void ConfigurationParser::parseConfigLine(const std::string &line, size_t &offset, Error *error)
{
	int i = 0;
	while (line[i] && !isspace(line[i]))
	{
		i++;
	}
	std::string name = line.substr(0, i);
	std::string lineAfterName = line.substr(i, line.length());
	std::cout << "got line <" << line << ">\n";
	std::cout << "checkign name \"" << name << "\"\n";
	i = 0;
	if (name.compare("workerProcesses") == 0)
	{
		parseWorkerProcesses(lineAfterName, offset, error);
		return ;
	}
	if (_serverParseFuncs.count(name) > 0)
	{
		configParserFunc func = _serverParseFuncs.at(name);
		(this->*func)(lineAfterName, offset, error);
	}
	else
	{
		error = new Error("cant parse line \"" + name +"\"");
		return ;
	}
	// offset += i;
	
}

void ConfigurationParser::parseEmbeddedLine(const std::string &lines, size_t &offset, Error *error)
{
	std::cout << "im in embedded <" << lines.substr(offset, 10) + ">\n";
	while(lines[offset] && !isalpha(lines[offset]))
	{
		offset++;
	}
	size_t offset_saver = offset;
	while (lines[offset] && !isspace(lines[offset]))
	{
		offset++;
	}
	std::string name = lines.substr(offset_saver, offset - offset_saver);
	if (name.compare("server") == 0)
	{
		ServerConfiguration serverConfiguration;
		_configuration.ServerConfigurations.push_front(serverConfiguration);
		std::cout << "i\n";
		parseServerConfiguration(lines, offset, error);
		if (error != nullptr)
		{
			return;
		}
		while (lines[offset] && !isalpha(lines[offset]))
		{
			offset++;
		}
		std::cout << "line after server <" << lines.substr(offset, 10) << std::endl;
	}
	else if (name.compare("errorPagesMap"))
	{
		parseErrorPagesMap(lines, offset, error);
	}
	else if (name.compare("location") == 0)
	{
		parseLocation(lines, offset, error);
	}
	else
	{
		error = new Error("uknown embedded config line \"" + name + "\"");
	}
}
