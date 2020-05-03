#include "NetworkService.h"

#include <boost/asio.hpp>
#include <iostream>
#include <stdexcept>

using namespace boost::asio;


UnAuthenticatedService* NetworkService::init()
{
	ioService_ = new io_service();
	return this;
}

UnAuthenticatedService* NetworkService::acceptConnection(const std::set<std::string>& trustedDomains)
{ 
	socket_t clientSocket = acceptConnection(7070); // listen on 7070
	std::string clientDomain = clientSocket.remote_endpoint().address().to_string();

	if (trustedDomains.find(clientDomain) == trustedDomains.end()) // return access denied to the connected user
		throw std::runtime_error("unsafe client origin");

	options = new RequestOptions(readRequestString(clientSocket));

	return this;
};


const AuthenticatedService* NetworkService::authenticateConnection(const std::map<std::string, std::string>& usersToAccept) const
{
	try {
		if (usersToAccept.at(options->userLogin()) != options->userPassword())
			throw std::runtime_error("user password does not match");
	}
	catch (const std::out_of_range& ex)
	{
		throw std::runtime_error("connected user does not listed");
	}
	
	return this;
}


std::string NetworkService::liveStreamUrl() const
{
	return options->streamLink();
}

std::string NetworkService::routingPath() const
{
	return options->routingPath();
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
	delete options;
	delete ioService_;
}
