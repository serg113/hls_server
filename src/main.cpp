#include "LiveStream.h"
#include "NetworkInterface.h"
#include "utils.h"
#include "tests.h"

#include <string>
#include <vector>
#include <map>


void run_app(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	/*
	 * in case of all functionality successfully tested
	 * run app
	 */
	//run_app(argc, argv);

	/* *
	 * test by terminal 
	 *    curl localhost:7070/frames-u:root-p:cm9vdDEyMzQ1NgDMzMzMzA==-a:http://192.168.99.1:8000/media/live-e:
	 * or
	 *    curl localhost:7070/record-u:root-p:cm9vdDEyMzQ1NgDMzMzMzA==-a:http://192.168.99.1:8000/media/live-e:
	 */
	testNetworkService(); 
}

void run_app(int argc, char* argv[])
{
	std::string jpegFolder = "./media/jpeg/";
	std::string videoFolder = "./media/video/";

	createFolderIfNotExist(jpegFolder);
	createFolderIfNotExist(videoFolder);

	std::map<std::string, std::string> existedUsersCredentials = { {"root", "cm9vdDEyMzQ1NgDMzMzMzA=="} };

	std::vector<std::string> trustedDomains = { "127.0.0.1", "192.168.99.1" };

	if (argc > 2 && argv[1] == "--trusted")
	{
		for (int i = 2; i < argc; ++i)
			trustedDomains.emplace_back(argv[i]);
	}

	// concrete classes can be changed, client should depend on interfaces
	auto service = createNetworkService()
		->waitConnectionFromTrustedDomains(trustedDomains); // running on port 7070

	if (service->connectionIsAuthenticated(existedUsersCredentials))
	{
		LiveStream liveStream(service->liveStreamUrl());

		if (service->routingPath() == "/frames")
			liveStream.saveFramesAsJpeg(jpegFolder);

		if (service->routingPath() == "/record")
			liveStream.saveFramesAsVideo(videoFolder);
	}
	

}
