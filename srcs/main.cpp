/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftassada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 03:10:46 by ftassada          #+#    #+#             */
/*   Updated: 2022/08/04 03:10:47 by ftassada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <string>

#include "RequestFactory.hpp"

#include "ConfigurationParser.hpp"
int main(int argc, char **argv)
{
	ConfigurationParser *parser = new ConfigurationParser();
	Configuration config = parser->parseConfig("./srcs/configuration/config.conf");
	delete parser;
	std::cout << "threadPool " << config.threadPoolSize << std::endl;
	std::cout << "port" << std::to_string(config.ServerConfigurations->port) << std::endl;
}
