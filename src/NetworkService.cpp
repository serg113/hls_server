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

	requestString_ = readRequestString(clientSocket);

	return this;
};


const AuthenticatedService* NetworkService::authenticateConnection(const std::map<std::string, std::string>& usersToAccept) const
{
	try {
		if (usersToAccept.at(extractUserLogin()) != extractUserPassword())
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
	return extractStreamLink();
}

std::string NetworkService::routingPath() const
{
	return extractRoutingPath();
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

std::string NetworkService::extractUserLogin() const
{
	return extractTag("-u:", "-p:"); // root
}

std::string NetworkService::extractUserPassword() const
{
	return extractTag("-p:", "-a:"); // cm9vdDEyMzQ1NgDMzMzMzA==
}

std::string NetworkService::extractRoutingPath() const
{
	return extractTag("/", "-u:"); // "frames" or "record"
}

std::string NetworkService::extractStreamLink() const
{
	return extractTag("-a:", "-e:");  // http://192.168.99.1:8000/media/live
}

std::string NetworkService::extractTag(const std::string& tag, const std::string& next) const
{
	//localhost:7070/frames-u:root-p:cm9vdDEyMzQ1NgDMzMzMzA==-a:http://192.168.99.1:8000/media/live-e:
	size_t startPos = requestString_.find(tag) + tag.size();
	size_t endPos = requestString_.find(next);
	return requestString_.substr(startPos, endPos - startPos);
}

