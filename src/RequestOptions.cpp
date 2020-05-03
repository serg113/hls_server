#include "RequestOptions.h"


RequestOptions::RequestOptions(const std::string& options) :request(options) { };

std::string RequestOptions::userLogin() const
{
	return extractTag("-u:", "-p:"); // root
}

std::string RequestOptions::userPassword() const
{
	return extractTag("-p:", "-a:"); // cm9vdDEyMzQ1NgDMzMzMzA==
}

std::string RequestOptions::routingPath() const
{
	return extractTag("/", "-u:"); // "frames" or "record"
}

std::string RequestOptions::streamLink() const
{
	return extractTag("-a:", "-e:");  // http://192.168.99.1:8000/media/live
}

std::string RequestOptions::extractTag(const std::string& tag, const std::string& next) const
{
	//localhost:7070/frames-u:root-p:cm9vdDEyMzQ1NgDMzMzMzA==-a:http://192.168.99.1:8000/media/live-e:
	size_t startPos = request.find(tag) + tag.size();
	size_t endPos = request.find(next);
	return request.substr(startPos, endPos - startPos);
}

