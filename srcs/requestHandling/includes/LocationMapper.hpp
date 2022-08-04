#ifndef LOCATIONMAPPER_HPP
# define LOCATIONMAPPER_HPP

# include "Request.hpp"
# include "Configuration.hpp"
# include "Error.hpp"

class LocationMapper
{
public:
	LocationMapper();
	~LocationMapper();

	LocationConfigurationUnit	const &mapLocation(
		Request const &request,
		ServerConfiguration ServerConfiguration,
		Error *err);
};

#endif
