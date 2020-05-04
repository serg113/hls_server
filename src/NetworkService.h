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
	NetworkService(const std::set<std::string>& trustedDomains);
	UnAuthenticatedService* init();

	const AuthenticatedService* acceptUsers(const std::map<std::string, std::string>& usersToAccept) override;

	std::string liveStreamUrl() const override;
	std::string routingPath() const override;
	 
	~NetworkService();

private:
	socket_t acceptConnection(size_t port) const;
	std::string readRequestString(socket_t& socket) const;
	void checkIfClientDomainIsTrusted(const socket_t& client) const;
	void checkIfCredentialsAreValid(const std::map<std::string, std::string>& usersToAccept) const;
	
	RequestOptions* options_;
	boost::asio::io_service* ioService_;
	std::set<std::string> trustedDomains_;
};

