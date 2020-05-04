#include "NetworkInterface.h"
#include "NetworkService.h"


UnAuthenticatedService* createNetworkService(const std::set<std::string>& trustedDomains)
{
	return (new NetworkService(trustedDomains))->init();
}