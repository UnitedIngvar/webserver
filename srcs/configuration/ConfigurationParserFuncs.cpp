/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParserFuncs.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftassada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 03:11:01 by ftassada          #+#    #+#             */
/*   Updated: 2022/08/05 15:49:39 by ftassada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigurationParser.hpp"

void ConfigurationParser::parseWorkerProcesses(const std::string &line, size_t &offset, std::string &error)
{
	std::cout << "worker processes" << line << std::endl;
	int threadPoolSize = atoi(line.c_str());
	if (threadPoolSize <= 0 && threadPoolSize >= 100)
	{
		error = "wrong worker processes line. min = 1, max = 100";
		return;
	}
	this->_configuration.threadPoolSize = threadPoolSize;
}

void ConfigurationParser::parseServerConfiguration(const std::string &lines,
	size_t &offset, std::string &error)
{
	size_t offset_saver = offset;
	while(lines[offset] && lines[offset] != '}')
	{
		while (lines[offset] && !isalpha(lines[offset]) && lines[offset] != '}')
		{
			offset++;
		}
		offset_saver = offset;
		while (lines[offset] && !isspace(lines[offset]) && lines[offset] != '}')
		{
			offset++;
		}

		std::string name = lines.substr(offset_saver, offset - offset_saver);
		std::cout << "\n NAME " + name + "\n";
		if (_serverParseFuncs.count(name) > 0)
		{
			configParserFunc func = _serverParseFuncs.at(name);
			(this->*func)(lines, offset, error);
			if (error != "")
			{
				return;
			}
		}
	}
}

void ConfigurationParser::parseListen(const std::string &lines, size_t &offset, std::string &error)
{
	size_t offset_saver = offset;
	while(lines[offset] && lines[offset] != ';' && lines[offset] != '\n')
	{
		offset++;
	}
	if (lines[offset] == '\n')
	{
		error = "no \";\" in server->listen line";
		return;
	}
	int listen = atoi(lines.substr(offset_saver, offset - offset_saver).c_str());
	if (listen <= 0)
	{
		error = "wrong server->listen line";
		return;
	}
	_configuration.ServerConfigurations.front()->port = listen;
	std::cout << _configuration.ServerConfigurations.front()->port << std::endl;
}

void ConfigurationParser::parseServerName(const std::string &lines, size_t &offset, std::string &error)
{
	int left_i_saver, i = 0;
	std::cout << line << "> LINE\n";
	while (line[i] && line[i] != ';')
	{
		while (line[i] && !isalpha(line[i]) && line[i] != ';' && line[i] != '\n')
		{
			i++;
		}
		left_i_saver = i;
		while (line[i] && !isspace(line[i]) && line[i] != ';' && line[i] != '\n')
		{
			i++;
		}
		switch (line[i])
		{
			case '\n':
				error = "no \";\" in server->serverName line";
				return;
			case ';':
				if (_configuration.ServerConfigurations.front()->serverNames.size() == 0)
				{
					error = "no server name[-s] was provided in server->serverName";
					return;
				}
			default:
				_configuration.ServerConfigurations.front()->serverNames.push_back(line.substr(left_i_saver, i - left_i_saver));
				i++;
				std::cout << "DOTA\n";
				continue;

		}
		// может добавить валидацию на УРЛ

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
		while (lines[offset] && !isdigit(lines[offset]))
		{
			offset++;
		}
		offset_saver = offset;
		while(lines[offset] && !isspace(lines[offset]))
		{
			offset++;
		}
		ResponseCodeRepresentation errCodeRepresentation = getCodeRepresentation(
			getErrorCodeFromInteger(std::stoi(lines.substr(offset_saver, offset).c_str())));
		if (std::stoi(errCodeRepresentation.number) == UknownCode)
		{
			error = "could not parse error page for error code <" + lines.substr(offset_saver, offset) + ">";
			return;
		}
		offset_saver = offset;
		while (lines[offset] && lines[offset] != '\n')
		{
			offset++;
		}
		std::string pathToErrorPageFile = lines.substr(offset_saver, offset - 1);
		File file(pathToErrorPageFile);
		FileOperationResult fileOpenResult = file.checkCanBeAccessed();
		if (fileOpenResult == NotFound)
		{
			error = "could not find file with error code <" + errCodeRepresentation.number +
			 "> Path: " + pathToErrorPageFile;
			return;
		}
		else if (fileOpenResult == AccessDenied)
		{
			error = "access denied to file with error page for error code <" + errCodeRepresentation.number +
			"> Path: " + pathToErrorPageFile;
			return;
		}
		_configuration.ServerConfigurations.front()->errorPagesMap.insert(
			std::pair<ResponseCode, std::string>(getErrorCodeFromInteger(std::stoi(errCodeRepresentation.number)), pathToErrorPageFile)
			);
	}
}

void ConfigurationParser::parseRedirection(const std::string &line, size_t &offset, std::string &error)
{

}

void ConfigurationParser::parseMaxBodySize(const std::string &line, size_t &offset, std::string &error)
{
	int i = std::stoi(line);
	if (i <= 0)
	{
		error = "wrong server->maxBodySize line";
		return;
	}
	_configuration.ServerConfigurations.front()->maxBodySize = i;
}

void ConfigurationParser::parseLocation(const std::string &lines, size_t &offset, std::string &error)
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
