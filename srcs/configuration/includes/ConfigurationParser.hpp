#ifndef CONFIGURATIONPARSER_HPP
# define CONFIGURATIONPARSER_HPP

# include <string>
# include "Configuration.hpp"
# include "File.hpp"

class ConfigurationParser
{
private:
	typedef void (ConfigurationParser::*configParserFunc)(const std::string &line, size_t &offset, std::string &error);

	Configuration configuration;
	configParserFunc *_arrayOfParseServerFuncs;
	std::string *_arrayOfParseServerFuncsNames;
	configParserFunc *_arrayOfParseLocationFuncs;
	std::string *_arrayOfParseLocationFuncsNames;

	void parseWorkerProcesses(const std::string &line, size_t &offset, std::string &error);
	void parseListen(const std::string &line, size_t &offset, std::string &error);
	void parseServerName(const std::string &line, size_t &offset, std::string &error);
	void parseRoot(const std::string &line, size_t &offset, std::string &error);
	void parseErrorPagesMap(const std::string &line, size_t &offset, std::string &error);
	void parseRedirection(const std::string &line, size_t &offset, std::string &error);
	void parseMaxBodySize(const std::string &line, size_t &offset, std::string &error);
	void parseLocation(const std::string &line, size_t &offset, std::string &error);
	void parseMethods(const std::string &line, size_t &offset, std::string &error);
	void parseDirectory(const std::string &line, size_t &offset, std::string &error);
	void parseIndexFile(const std::string &line, size_t &offset, std::string &error);
	void parseCgiExtension(const std::string &line, size_t &offset, std::string &error);
	void parseDirListOn(const std::string &line, size_t &offset, std::string &error);

	void parseConfigLine(const std::string &line, size_t &offset, std::string &error);
	void parseEmbeddedLine(const std::string &lines, size_t &offset, std::string &error);
public:
	ConfigurationParser();
	~ConfigurationParser();

	Configuration parseConfig(std::string pathToFile);

	class FileReadException : public std::exception
	{
	// TODO: докинуть сюда FileOperationResult
	private:
		std::string			_filePath;

	public:
		FileReadException(std::string filePath);

		virtual const char	*what() const throw();
	};

	class ConfigurationFormatError : public std::exception
	{
	public:
		ConfigurationFormatError();

	// TODO: докинуть сюда FileOperationResult
	private:
		std::string			_filePath;

	public:
		ConfigurationFormatError(std::string filePath);
	public:
		ConfigurationFormatError();

		virtual const char	*what() const throw();
	};
};

#endif
