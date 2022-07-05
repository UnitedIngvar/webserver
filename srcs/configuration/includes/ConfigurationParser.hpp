#ifndef CONFIGURATIONPARSER_HPP
# define CONFIGURATIONPARSER_HPP

# include <string>
# include "Configuration.hpp"
# include "File.hpp"

class ConfigurationParser
{
private:

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
};

#endif
