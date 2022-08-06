#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

# include "RequestMethod.hpp"
# include "ResponseCode.hpp"
# include <string>
# include <map>

typedef struct LocationConfigurationUnit
{
	RequestMethod	*acceptedMethods;
	std::string	redirectionPath;
	std::string	url;
	std::string	directory;
	std::string	indexFile;
	std::string	cgiExtension;
	bool	directoryListingOn;
} LocationConfigurationUnit;

typedef struct ServerConfiguration
{
	std::map<std::string, LocationConfigurationUnit>	locationMap;
	std::map<ResponseCode, std::string>	errorPagesMap;
	std::string	redirectionPath;
	std::string	serverName;
	unsigned int	host; // IP
	int	port;
	int	maxBodySize;
} ServerConfiguration;

typedef struct Configuration
{
	ServerConfiguration	*ServerConfigurations;
	int	threadPoolSize;
} Configuration;

#endif
