#pragma once
#include <string>
#include <set>
#include <map>

/* 
  interface for client
*/

/*  Service initialization consists of two function calls
	ex.
		auto service = createNetworkService(domains)->acceptUsers(credentials);

	after initialization object will provide an interface for internal data
	ex.
		std::string url = service->liveStreamUrl();
		std::string routPath = service->routingPath();

	note: initialized object is immutable (we cannot change it's internal state after successful initialization)
*/ 

class AuthenticatedService
{
public:
	virtual std::string liveStreamUrl() const = 0;
	virtual std::string routingPath() const = 0;
};

class UnAuthenticatedService
{
public:
	virtual const AuthenticatedService* acceptUsers(const std::map<std::string, std::string>& usersToAccept) = 0;
};


UnAuthenticatedService* createNetworkService(const std::set<std::string>& trustedDomains);
