#pragma once
#include <string>
#include <set>
#include <map>


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
