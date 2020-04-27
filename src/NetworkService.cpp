#include "NetworkService.h"

#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

void NetworkService::waitConnectionFromTrustedDomains(const std::vector<std::string>& trustedDomains) 
{ 
	// a lot of mess
	io_service* service = new io_service(); // make shared
	ip::tcp::acceptor acceptor_server(*service, ip::tcp::endpoint(ip::tcp::v4(), 7070)); // listen on 7070
	socket_ptr server_socket = new ip::tcp::socket(*service); // make shared

	acceptor_server.accept(*server_socket);

	initConnectionIfTrusted(trustedDomains, server_socket);
};

bool NetworkService::connectionIsEstablishedAndAuthenticated(const std::map<std::string, std::string>& knownUsers)
{
	std::string requestString = readRequestString(); // curl localhost:7070/frames-l-http://192.168.99.1:8000/media/live-

	if (knownUsers.at(extractUserLogin(requestString)) == extractUserPassword(requestString))
	{
		routingPath_ = extractRoutingPath(requestString); // "/frames" or "/record"
		liveStreamUrl_ = extractStreamLink(requestString); // http://192.168.99.1:8000/media/live
	}
	return true;
}


std::string NetworkService::liveStreamUrl() const
{
	return liveStreamUrl_;
}

bool NetworkService::routPathEquals(const std::string& routPath) const
{
	return routingPath_ == routPath;
}

std::string NetworkService::readRequestString() const
{
	streambuf buf;
	read_until(*serverSocket_, buf, "\n");
	return buffer_cast<const char*>(buf.data());;
}

void NetworkService::initConnectionIfTrusted(const std::vector<std::string>& trustedDomains, socket_ptr socket)
{
	std::string connectionAddress = socket->remote_endpoint().address().to_string();

	for (auto addr : trustedDomains) {
		if (addr == connectionAddress) {
			serverSocket_ = socket;
		}
	}
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
