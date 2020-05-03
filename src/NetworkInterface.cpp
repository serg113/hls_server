#include "NetworkInterface.h"
#include "NetworkService.h"


UnAuthenticatedService* createNetworkService()
{
	return (new NetworkService())->init();
}