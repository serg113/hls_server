#include "NetworkService.h"

#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;


UnAuthenticatedService* NetworkService::init()
{
	ioService_ = new io_service();	// class needs io_service existence during it's lifetime

	return this;
}

AuthenticatedService* NetworkService::waitConnectionFromTrustedDomains(const std::vector<std::string>& trustedDomains)
{ 
	ip::tcp::acceptor acceptor_server(*ioService_, ip::tcp::endpoint(ip::tcp::v4(), 7070)); // listen on 7070
	socket_ptr server_socket = new ip::tcp::socket(*ioService_); // make shared or can be used copy instead ??

	acceptor_server.accept(*server_socket);

	initRequestStringIfTrusted(trustedDomains, server_socket);

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


void NetworkService::initRequestStringIfTrusted(const std::vector<std::string>& trustedDomains, socket_ptr socket)
{
	std::string connectionAddress = socket->remote_endpoint().address().to_string();

	for (auto addr : trustedDomains) {
		if (addr == connectionAddress) {
			requestString_ = readRequestString(socket);
		}
	}
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
