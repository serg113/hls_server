#pragma once
#include <string>
#include <set>
#include <map>


class AuthenticatedService
{
public:
	virtual bool connectionIsAuthenticated(const std::map<std::string, std::string>& usersToAccept) const = 0;
	virtual std::string liveStreamUrl() const = 0;
	virtual std::string routingPath() const = 0;
};

class UnAuthenticatedService
{
public:
	virtual AuthenticatedService* waitConnectionFromTrustedDomains(const std::set<std::string>& trustedDomains) = 0;
};


UnAuthenticatedService* createNetworkService(/*
	const std::vector<std::string>& trustedDomains,
	const std::map<std::string, std::string>& usersToAccept*/
);
