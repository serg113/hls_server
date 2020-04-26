#include "TrustedSocket.h"



TrustedSocket::TrustedSocket(const std::vector<std::string>& trustedDomains) : trustedDomains_(trustedDomains)
{ };

void TrustedSocket::listenAndAuthenticateAndSetRoutAndSetURL(const std::map<std::string, std::string>& usersToAccept)
{
	// waiting to accept user
}

std::string TrustedSocket::liveStreamUrl() const
{
	return liveStreamUrl_;
}

bool TrustedSocket::routPathIs(const std::string& routPath) const
{
	return routingPath_ == routPath;
}