#pragma once
#include "NetworkInterface.h"

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <set>
#include <map>


using socket_t = boost::asio::ip::tcp::socket;


// todo: separate three responsibilities of this class to avoid violation of SRP: 
//	1. connection 
//	2. authentication 
//	3. requested options
class NetworkService : UnAuthenticatedService, AuthenticatedService
{
public:
	UnAuthenticatedService* init();

	virtual UnAuthenticatedService* acceptConnection(const std::set<std::string>& trustedDomains) override;
	virtual const AuthenticatedService* authenticateConnection(const std::map<std::string, std::string>& usersToAccept) const override;

	std::string liveStreamUrl() const override;
	std::string routingPath() const override;

private:
	socket_t acceptConnection(size_t port) const;

	std::string readRequestString(socket_t& socket) const;
	std::string extractUserLogin(const std::string& requestString) const;
	std::string extractUserPassword(const std::string& requestString) const;
	std::string extractRoutingPath(const std::string& requestString) const;
	std::string extractStreamLink(const std::string& requestString) const;

	std::string requestString_;
	boost::asio::io_service* ioService_;
};




