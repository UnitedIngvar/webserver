/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftassada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 03:11:07 by ftassada          #+#    #+#             */
/*   Updated: 2022/08/04 13:42:01 by ftassada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

# include "RequestMethod.hpp"
# include "ResponseCode.hpp"
# include <string>
# include <map>
# include <list>

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
	std::list<std::string>	serverNames;
	unsigned int	host; // IP
	int	port;
	int	maxBodySize;
} ServerConfiguration;

typedef struct Configuration
{
	std::list<ServerConfiguration>ServerConfigurations;
	int	threadPoolSize;
} Configuration;

#endif
