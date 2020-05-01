#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <vector>
#include <map>

typedef boost::asio::ip::tcp::socket* socket_ptr;

// here are three classes 
//		and three responsibilities: 
//									1. connection 
//									2. authentication 
//									3. requested options
//
// reasons currently I need to change the class are 
// 1. connection with another method, not tcp socket
// 2. if authentication method changes
// 3. if parsing request string format will be changed

class NetworkService 
{
public:
	void waitConnectionFromTrustedDomains(const std::vector<std::string>& trustedDomains);
	bool connectionIsAuthenticated(const std::map<std::string, std::string>& usersToAccept);

	std::string liveStreamUrl() const;
	std::string routingPath() const;

private:
	void initRequestStringIfTrusted(const std::vector<std::string>& trustedDomains, socket_ptr socket);

	std::string readRequestString(socket_ptr socket) const;
	std::string extractUserLogin(const std::string& requestString) const;
	std::string extractUserPassword(const std::string& requestString) const;
	std::string extractRoutingPath(const std::string& requestString) const;
	std::string extractStreamLink(const std::string& requestString) const;

	std::string requestString_;
};

