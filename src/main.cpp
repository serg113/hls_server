

#include "LiveStream.h"
#include "NetworkService.h"
#include "utils.h"
#include "tests.h"

#include <string>
#include <vector>
#include <map>


void run_app(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	//run_app(argc, argv);

	testSocket();
	//testLiveStream();
	//testBase64();
}

void run_app(int argc, char* argv[])
{
	std::string jpegFolder = "./media/jpeg/";
	std::string videoFolder = "./media/video/";

	createFolderIfNotExist(jpegFolder);
	createFolderIfNotExist(videoFolder);

	std::map<std::string, std::string> existedUsersCredentials = { {"root", "hash777"} };

	std::vector<std::string> trustedDomains = { "127.0.0.1", "192.168.99.1" };

	if (argc > 2 && argv[1] == "--trusted")
	{
		for (int i = 2; i < argc; ++i)
			trustedDomains.push_back(argv[i]);
	}


	NetworkService service;

	service.waitConnectionFromTrustedDomains(trustedDomains); // running on port 7070

	if (service.connectionIsEstablishedAndAuthenticated(existedUsersCredentials))
	{
		LiveStream liveStream(service.liveStreamUrl());

		if (service.routPathEquals("/frames"))
			liveStream.saveFramesAsJpeg(jpegFolder);

		if (service.routPathEquals("/record"))
			liveStream.saveFramesAsVideo(videoFolder);
	}
	

}
