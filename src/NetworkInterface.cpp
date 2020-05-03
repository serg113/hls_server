#include "NetworkInterface.h"
#include "NetworkService.h"


UnAuthenticatedService* createNetworkService(/*
	const std::vector<std::string>& trustedDomains,
	const std::map<std::string, std::string>& usersToAccept*/
)
{
	return (new NetworkService())->init();
}