#pragma once

#include <string>

class RequestOptions
{
public:
	RequestOptions(const std::string& options);
	std::string userLogin() const;
	std::string userPassword() const;
	std::string routingPath() const;
	std::string streamLink() const;

private:
	std::string extractTag(const std::string& tag, const std::string& next) const;
	std::string request;
};
