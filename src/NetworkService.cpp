#include "NetworkService.h"

#include <boost/asio.hpp>
#include <iostream>
#include <stdexcept>

using namespace boost::asio;


UnAuthenticatedService* NetworkService::init()
{
	ioService_ = new io_service();	// class needs io_service instance during it's lifetime

	return this;
}

AuthenticatedService* NetworkService::waitConnectionFromTrustedDomains(const std::vector<std::string>& trustedDomains)
{ 
	socket_ptr clientSocket = acceptNewConnection(7070);

	if (!clientIsTrusted(trustedDomains, clientSocket))
		throw std::runtime_error("unsafe client origin");

	requestString_ = readRequestString(clientSocket);

	return this;
};


bool NetworkService::connectionIsAuthenticated(const std::map<std::string, std::string>& knownUsers)
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


socket_ptr NetworkService::acceptNewConnection(size_t port)
{
	socket_ptr client = new ip::tcp::socket(*ioService_);
	ip::tcp::acceptor acceptor(*ioService_, ip::tcp::endpoint(ip::tcp::v4(), 7070)); // listen on 7070
	acceptor.accept(*client);

	return client;
}

bool NetworkService::clientIsTrusted(const std::vector<std::string>& trustedDomains, socket_ptr socket)
{
	std::string connectionAddress = socket->remote_endpoint().address().to_string();

	for (auto addr : trustedDomains) {
		if (addr == connectionAddress) {
			return true;
		}
	}
	return false;
}

std::string NetworkService::readRequestString(socket_ptr socket) const
{
	streambuf buf;
	read_until(*socket, buf, "\n");
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
