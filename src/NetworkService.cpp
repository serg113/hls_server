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

AuthenticatedService* NetworkService::waitConnectionFromTrustedDomains(const std::set<std::string>& trustedDomains)
{ 
	socket_t clientSocket = acceptConnection(7070); // listen on 7070
	std::string clientDomain = clientSocket.remote_endpoint().address().to_string();

	// Here we ensure double check, first one need to be configured by os. Do we really need it if os handles this case???
	if (trustedDomains.find(clientDomain) == trustedDomains.end())
		throw std::runtime_error("unsafe client origin");

	requestString_ = readRequestString(clientSocket);

	return this;
};


bool NetworkService::connectionIsAuthenticated(const std::map<std::string, std::string>& knownUsers) const
{
	return knownUsers.at(extractUserLogin(requestString_)) == extractUserPassword(requestString_);
}


std::string NetworkService::liveStreamUrl() const
{
	return extractStreamLink(requestString_);
}

std::string NetworkService::routingPath() const
{
	return extractRoutingPath(requestString_);
}


socket_t NetworkService::acceptConnection(size_t port) const
{
	socket_t client(*ioService_);// = new ip::tcp::socket(*ioService_);
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

std::string NetworkService::extractUserLogin(const std::string& requestString) const
{
	return "root"; // only available user
}

std::string NetworkService::extractUserPassword(const std::string& requestString) const
{
	return "cm9vdDEyMzQ1NgDMzMzMzA=="; //"root123456" 
}

std::string NetworkService::extractRoutingPath(const std::string& requestString) const
{
	//localhost:7070/frames-u:root-p:cm9vdDEyMzQ1NgDMzMzMzA==-a:http://192.168.99.1:8000/media/live-e:
	return requestString.substr(requestString.find('/'), 7); // "/frames" or "/record"
}

std::string NetworkService::extractStreamLink(const std::string& requestString) const
{
	//localhost:7070/frames-u:root-p:cm9vdDEyMzQ1NgDMzMzMzA==-a:http://192.168.99.1:8000/media/live-e:
	size_t startPos = requestString.find("-a:") + 3;
	size_t length = requestString.find("-e:") - startPos;
	auto link = requestString.substr(startPos, length);
	return link;  // http://192.168.99.1:8000/media/live
}
