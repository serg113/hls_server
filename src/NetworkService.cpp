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

	std::string connectionAddress = server_socket->remote_endpoint().address().to_string();

	for (auto addr : trustedDomains) {
		if (addr == connectionAddress){
			std::cout << addr << "==" << connectionAddress << std::endl;
			serverSocket_ = server_socket;
		}
	}
};

bool NetworkService::connectionEstablishedAndAuthenticated(const std::map<std::string, std::string>& knownUsers)
{
	// check if connected user is in knownUsers, then read commands and set rout and stream link
	streambuf buf;

	read_until(*serverSocket_, buf, "\n");

	std::string data = buffer_cast<const char*>(buf.data());
	std::cout << data << std::endl;

	// curl localhost:7070/frames-l-http://192.168.99.1:8000/media/live-
	auto rout = data.substr(data.find('/'), 7); // "/frames" or "/record"
	std::cout << "rout: " << rout << std::endl;

	size_t linkLength = data.find("-", data.find("-l-") + 3) - (data.find("-l-") + 3);
	auto link = data.substr(data.find("-l-") + 3, linkLength);

	std::cout << "link: " << link << std::endl; // http://192.168.99.1:8000/media/live

	routingPath_ = rout;
	liveStreamUrl_ = link;

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