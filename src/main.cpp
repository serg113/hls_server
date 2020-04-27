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
	/*
	 * in case of all functionality successfully tested
	 * run app
	 */
	//run_app(argc, argv);

	/* 
	 * call from any terminal 
	 * 
	 *    curl localhost:7070/frames-l-http://192.168.99.1:8000/media/live-
	 * or
	 *    curl localhost:7070/record-l-http://192.168.99.1:8000/media/live-
	 */
	testSocket(); 

	/*
	 * for runninng live stream server we can run this test 
	 * functions calls is hardcoded with parameters 
	 *		http://192.168.99.1:8000/media/live
	 *		./media/jpeg/
	 *		./media/video/
	 *
	 */
	//testLiveStream();

	// base64 encoding - decoding test, from boost library
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
