#pragma once
#include "NetworkInterface.h"
#include "RequestOptions.h"

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <set>
#include <map>


using socket_t = boost::asio::ip::tcp::socket;


// todo: separate three responsibilities of this class to avoid violation of SRP: 
//	1. connection 
//	2. authentication 
//  3. request options --> moved to RequestOptions class
class NetworkService : UnAuthenticatedService, AuthenticatedService
{
public:
	UnAuthenticatedService* init();

	UnAuthenticatedService* acceptConnection(const std::set<std::string>& trustedDomains) override;
	const AuthenticatedService* authenticateConnection(const std::map<std::string, std::string>& usersToAccept) const override;

	std::string liveStreamUrl() const override;
	std::string routingPath() const override;

	~NetworkService();

private:
	socket_t acceptConnection(size_t port) const;
	std::string readRequestString(socket_t& socket) const;
	
	RequestOptions* options;
	boost::asio::io_service* ioService_;
};

