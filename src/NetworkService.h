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
	bool connectionEstablishedAndAuthenticated(const std::map<std::string, std::string>& usersToAccept);

	std::string liveStreamUrl() const;
	bool routPathEquals(const std::string& routPath) const;

private:
	std::string liveStreamUrl_;
	std::string routingPath_;
	socket_ptr serverSocket_;
};

