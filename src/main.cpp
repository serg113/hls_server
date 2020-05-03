#include "LiveStream.h"
#include "NetworkInterface.h"
#include "utils.h"
#include "tests.h"

#include <string>
#include <set>
#include <map>
#include <exception>


void run_app(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	//run_app(argc, argv);

	/*
	 * hint will be printed on console
	 * call
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

	std::set<std::string> trustedDomains = { "127.0.0.1", "192.168.99.1" };

	if (argc > 2 && argv[1] == "--trusted")
	{
		for (int i = 2; i < argc; ++i)
			trustedDomains.emplace(argv[i]);
	}

	try {
		auto service = createNetworkService()
			->acceptConnection(trustedDomains)
			->authenticateConnection(existedUsersCredentials);


		LiveStream liveStream(service->liveStreamUrl());

		if (service->routingPath() == "frames")
			liveStream.saveFramesAsJpeg(jpegFolder);

		if (service->routingPath() == "record")
			liveStream.saveFramesAsVideo(videoFolder);
	}
	catch (const std::exception& ex)
	{
		std::cout << "[error] " << ex.what() << std::endl;
	}

}
