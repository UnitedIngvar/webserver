#ifndef GATEWAYFACTORY_HPP
# define GATEWAYFACTORY_HPP

# include "IGateway.hpp"
# include "LocationMapper.hpp"

class GatewayFactory
{
private:
	LocationMapper _locationMapper;

public:
	GatewayFactory();
	~GatewayFactory();

	IGateway	create(
		Request const *request,
		ServerConfiguration ServerConfiguration,
		Error *error);
};

#endif
