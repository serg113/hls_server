#pragma once
#include "NetworkInterface.h"

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <vector>
#include <map>

typedef boost::asio::ip::tcp::socket* socket_ptr;


// todo: separate three responsibilities of this class to avoid violation of SRP: 
//	1. connection 
//	2. authentication 
//	3. requested options
class NetworkService : UnAuthenticatedService, AuthenticatedService
{
public:
	UnAuthenticatedService* init();

	AuthenticatedService* waitConnectionFromTrustedDomains(const std::vector<std::string>& trustedDomains) override;
	bool connectionIsAuthenticated(const std::map<std::string, std::string>& usersToAccept) override;

	std::string liveStreamUrl() const override;
	std::string routingPath() const override;

private:
	void initRequestStringIfTrusted(const std::vector<std::string>& trustedDomains, socket_ptr socket);

	std::string readRequestString(socket_ptr socket) const;
	std::string extractUserLogin(const std::string& requestString) const;
	std::string extractUserPassword(const std::string& requestString) const;
	std::string extractRoutingPath(const std::string& requestString) const;
	std::string extractStreamLink(const std::string& requestString) const;

	std::string requestString_;
	boost::asio::io_service* ioService_;
};




