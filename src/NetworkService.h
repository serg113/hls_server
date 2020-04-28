#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <vector>
#include <map>

typedef boost::asio::ip::tcp::socket* socket_ptr;

class NetworkService
{
public:
	void waitConnectionFromTrustedDomains(const std::vector<std::string>& trustedDomains);
	bool connectionIsAuthenticated(const std::map<std::string, std::string>& usersToAccept);

	std::string liveStreamUrl() const;
	bool routPathEquals(const std::string& routPath) const;

private:
	void initRequestStringIfTrusted(const std::vector<std::string>& trustedDomains, socket_ptr socket);

	std::string readRequestString(socket_ptr socket) const;
	std::string extractUserLogin(const std::string& requestString) const;
	std::string extractUserPassword(const std::string& requestString) const;
	std::string extractRoutingPath(const std::string& requestString) const;
	std::string extractStreamLink(const std::string& requestString) const;


	std::string liveStreamUrl_;
	std::string routingPath_;
	std::string requestString_;
};

