#include "NetworkService.h"

#include <boost/asio.hpp>
#include <stdexcept>

#define PORT 7070

using namespace boost::asio;

NetworkService::NetworkService(const std::set<std::string>& trustedDomains) : trustedDomains_(trustedDomains) {};

UnAuthenticatedService* NetworkService::init()
{
	ioService_ = new io_service();
	return this;
}

const AuthenticatedService* NetworkService::acceptUsers(const std::map<std::string, std::string>& usersToAccept)
{
	socket_t client = acceptConnection(PORT);

	checkIfClientDomainIsTrusted(client);

	RequestOptions options(readRequestString(client));

	checkIfCredentialsAreValid(usersToAccept, options);

	options_ = new RequestOptions(options);

	return this;
}

void NetworkService::checkIfClientDomainIsTrusted(const socket_t& client) const
{
	std::string clientDomain = client.remote_endpoint().address().to_string();

	if (trustedDomains_.find(clientDomain) == trustedDomains_.end())
		throw std::runtime_error("unsafe client origin");
}

void NetworkService::checkIfCredentialsAreValid(const std::map<std::string, std::string>& usersToAccept, const RequestOptions& options) const
{
	try
	{
		if (usersToAccept.at(options.userLogin()) != options.userPassword())
			throw std::runtime_error("user password does not match");
	}
	catch (const std::out_of_range& ex)
	{
		throw std::runtime_error("connected user does not listed");
	}
}


std::string NetworkService::liveStreamUrl() const
{
	return options_->streamLink();
}

std::string NetworkService::routingPath() const
{
	return options_->routingPath();
}


socket_t NetworkService::acceptConnection(size_t port) const
{
	socket_t client(*ioService_);
	ip::tcp::acceptor acceptor(*ioService_, ip::tcp::endpoint(ip::tcp::v4(), port)); 
	acceptor.accept(client);

	return client;
}


std::string NetworkService::readRequestString(socket_t& socket) const
{
	streambuf buf;
	read_until(socket, buf, "\n");
	return buffer_cast<const char*>(buf.data());
}

NetworkService::~NetworkService()
{
	delete options_;
	delete ioService_;
}
