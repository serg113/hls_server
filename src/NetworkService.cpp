#include "NetworkService.h"

#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

void NetworkService::waitConnectionFromTrustedDomains(const std::vector<std::string>& trustedDomains) 
{ 
	io_service* service = new io_service(); // make shared
	ip::tcp::acceptor acceptor_server(*service, ip::tcp::endpoint(ip::tcp::v4(), 7070)); // listen on 7070
	socket_ptr server_socket = new ip::tcp::socket(*service); // make shared

	acceptor_server.accept(*server_socket);

	initRequestStringIfTrusted(trustedDomains, server_socket);
};


bool NetworkService::connectionIsAuthenticated(const std::map<std::string, std::string>& knownUsers)
{
	return knownUsers.at(extractUserLogin(requestString_)) == extractUserPassword(requestString_);
}


std::string NetworkService::liveStreamUrl() const
{
	return extractStreamLink(requestString_);
}

bool NetworkService::routPathEquals(const std::string& routPath) const
{
	return routPath == extractRoutingPath(requestString_);;
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
	return buffer_cast<const char*>(buf.data());;
}

std::string NetworkService::extractUserLogin(const std::string& requestString) const
{
	return "root"; // only available user
}

std::string NetworkService::extractUserPassword(const std::string& requestString) const
{
	return "cm9vdDEyMzQ1NgDMzMzMzA=="; //"root123456" 
}

std::string NetworkService::extractRoutingPath(const std::string& requestString) const
{
	return requestString.substr(requestString.find('/'), 7); // "/frames" or "/record"
}

std::string NetworkService::extractStreamLink(const std::string& requestString) const
{
	size_t linkLength = requestString.find("-", requestString.find("-l-") + 3) - (requestString.find("-l-") + 3);
	auto link = requestString.substr(requestString.find("-l-") + 3, linkLength);
	return link;  // http://192.168.99.1:8000/media/live
}
