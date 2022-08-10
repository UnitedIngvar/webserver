#ifndef CONFIGURATIONPARSER_HPP
# define CONFIGURATIONPARSER_HPP

#include <string>
#include "Configuration.hpp"
#include "File.hpp"
#include "Error.hpp"

class ConfigurationParser
{
private:
	typedef void (ConfigurationParser::*configParserFunc)(const std::string &line, size_t &offset, Error *error);

	Configuration _configuration;
	std::map<std::string, void(*)> _serverMap;
	std::map<std::string, configParserFunc> _serverParseFuncs;
	std::map<std::string, configParserFunc> _locationParseFuncs;

	void parseWorkerProcesses(const std::string &line, size_t &offset, Error *error);
	void parseServerConfiguration(const std::string &line, size_t &offset, Error *error);
	void parseListen(const std::string &line, size_t &offset, Error *error);
	void parseServerName(const std::string &line, size_t &offset, Error *error);
	void parseRoot(const std::string &line, size_t &offset, Error *error);
	void parseErrorPagesMap(const std::string &line, size_t &offset, Error *error);
	void parseRedirection(const std::string &line, size_t &offset, Error *error);
	void parseMaxBodySize(const std::string &line, size_t &offset, Error *error);

	void parseLocation(const std::string &lines, size_t &offset, Error *error);
	void parseMethods(const std::string &line, size_t &offset, Error *error);
	void parseDirectory(const std::string &line, size_t &offset, Error *error);
	void parseIndexFile(const std::string &line, size_t &offset, Error *error);
	void parseCgiExtension(const std::string &line, size_t &offset, Error *error);
	void parseDirListOn(const std::string &line, size_t &offset, Error *error);

	void parseConfigLine(const std::string &line, size_t &offset, Error *error);
	void parseEmbeddedLine(const std::string &lines, size_t &offset, Error *error);

	void validateLine(const std::string &line, size_t &offset, const std::string &lineName, Error *error);
public:
	ConfigurationParser();

	Configuration parseConfig(std::string pathToFile);

};

#endif
