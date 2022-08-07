#include "GatewayFactory.hpp"

GatewayFactory::GatewayFactory()
{

}

GatewayFactory::~GatewayFactory()
{

}

IGateway	GatewayFactory::create(
	Request const *request,
	ServerConfiguration ServerConfiguration,
	Error *error)
{
	throw std::exception(); // TODO: not implemented
}
