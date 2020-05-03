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
	virtual UnAuthenticatedService* acceptConnection(const std::set<std::string>& trustedDomains) = 0;
	virtual const AuthenticatedService* authenticateConnection(const std::map<std::string, std::string>& usersToAccept) const = 0;
};


UnAuthenticatedService* createNetworkService();
