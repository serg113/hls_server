#include "LiveStream.h"
#include "TrustedSocket.h"

#include "tests.h"

#include <string>
#include <vector>
#include <map>

void run_app(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	//run_app(argc, argv);

	runAllTests();
}

void run_app(int argc, char* argv[])
{
	std::string jpegFolder = "./media/jpeg/";
	std::string videoFolder = "./media/video/";

	std::map<std::string, std::string> users = { {"root", "hash777"} };

	std::vector<std::string> domainsToAccept = { "127.0.0.1", "192.168.99.1" };

	if (argc > 2 && argv[1] == "--trusted")
	{
		for (int i = 2; i < argc; ++i)
			domainsToAccept.push_back(argv[i]);
	}

	TrustedSocket socket(domainsToAccept); // running on port 7070

	// this is a super-super socket // violates single responsibility principle
	socket.listenAndAuthenticateAndSetRoutAndSetURL(users);

	LiveStream liveStream(socket.liveStreamUrl());

	if (socket.routPathIs("/frames"))
		liveStream.saveFramesAsJpeg(jpegFolder);

	if (socket.routPathIs("/record"))
		liveStream.saveFramesAsVideo(videoFolder);

}
