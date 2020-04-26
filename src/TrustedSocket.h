#pragma once
#include <string>
#include <vector>
#include <map>

class TrustedSocket
{
public:
	TrustedSocket(const std::vector<std::string>& trustedDomains);

	// the super function
	void listenAndAuthenticateAndSetRoutAndSetURL(const std::map<std::string, std::string>& usersToAccept);

	std::string liveStreamUrl() const;
	bool routPathIs(const std::string& routPath) const;

private:
	const std::vector<std::string> trustedDomains_;
	std::string liveStreamUrl_;
	std::string routingPath_;
};

