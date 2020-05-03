#include "NetworkInterface.h"
#include "LiveStream.h"
#include "utils.h"
#include "tests.h"

#include <iostream>
#include <string>
#include <exception>

#include <boost/beast/core/detail/base64.hpp>


// only checking of valid cases

void testBase64()
{
	using namespace boost::beast::detail::base64;

	std::string word = "root123456"; //at least 10 charachters
	size_t len = word.length();
	std::string encoded = "cm9vdDEyMzQ1NgDMzMzMzA==";
	
	//encode((void*)(encoded.c_str()), (void*)(word.c_str()), encoded_size(len));

	//std::cout << "encoding --> " << word << " --> " << encoded.c_str() << std::endl;

	std::string decoded;

	decode((void*)(decoded.c_str()), encoded.c_str(), decoded_size(encoded.length()));

	std::cout << "decoding --> "<< encoded.c_str() << " --> " << decoded.c_str()<< std::endl;
}


void testNetworkService() 
{
	try {

		std::cout << 
			"trusted ips: 127.0.0.1, 192.168.99.1 \n\n"
			"to see test results, run in terminal \n"
			"    curl localhost:7070/frames-u:root-p:cm9vdDEyMzQ1NgDMzMzMzA==-a:http://192.168.99.1:8000/media/live-e:\n"
			"or\n"
			"    curl localhost:7070/record-u:root-p:cm9vdDEyMzQ1NgDMzMzMzA==-a:http://192.168.99.1:8000/media/live-e:\n"
			<< std::endl;
		std::cout << "[start] waiting for connection" << std::endl;

		auto service = createNetworkService()
			->waitConnectionFromTrustedDomains({ "127.0.0.1", "192.168.99.1" });

		std::cout << "\n[ok] connection established" << std::endl;
		if (service->connectionIsAuthenticated({ {"root", "cm9vdDEyMzQ1NgDMzMzMzA=="} })) // root123456
		{
			std::cout << "\n[ok] connection authenticated" << std::endl;
			if (service->routingPath() == "/frames")
			{
				std::cout << "\n[ok] routing path: /frames" << std::endl;
				testSavingLiveStreamAsJpeg(service->liveStreamUrl());
			}
			else if (service->routingPath() == "/record")
			{
				std::cout << "\n[ok] routing path: /record" << std::endl;
				testSavingLiveStreamAsVideo(service->liveStreamUrl());
			}
			else
				std::cout << "\n[error] routing path not recognaized" << std::endl;

			std::cout << "\n[info] user provided live link: " << service->liveStreamUrl() << std::endl;

			std::cout << "\n[end] connection test passed" << std::endl;
		}
	}
	catch (const std::exception & ex)
	{
		std::cout << "\n[end] connection test failed" << std::endl;
	}
}

void testLiveStreamProcessing()
{
	std::cout << "test 1/2 --> saving stream as jpeg  : ";
	testSavingLiveStreamAsJpeg("http://192.168.99.1:8000/media/live") ? std::cout << "passed\n" : std::cout << "failed\n";
	
	std::cout << "test 2/2 --> saving stream as video : ";
	testSavingLiveStreamAsVideo("http://192.168.99.1:8000/media/live") ? std::cout << "passed\n" : std::cout << "failed\n";
}


bool testSavingLiveStreamAsJpeg(std::string url)
{
	bool success = true;

	std::cout << "\n[start] saving stream as jpeg, stream url:" << url << std::endl;
	try {
		LiveStream stream(url);

		std::cout << "\n[info] creating folder if not exist: " << "./media/jpeg/" << std::endl;
		createFolderIfNotExist("./media/jpeg/");

		std::cout << "\n[info] saving frames ... " << std::endl;
		stream.saveFramesAsJpeg("./media/jpeg/");
		std::cout << "\n[end] frames are successfully saved" << std::endl;
	}
	catch (const std::exception& ex) {
		success = false;
		std::cout << "\n[end] frames saving failed" << std::endl;
	}

	return success;
}

bool testSavingLiveStreamAsVideo(std::string url)
{
	bool success = true;
	std::cout << "\n[start] saving stream as jpeg, stream url:" << url << std::endl;

	try {
		LiveStream stream(url);

		std::cout << "\n[info] creating folder if not exist: " << "./media/video/" << std::endl;
		createFolderIfNotExist("./media/video/");

		std::cout << "\n[info] recording video ... " << std::endl;
		stream.saveFramesAsVideo("./media/video/");
		std::cout << "\n[end] video file successfully saved" << std::endl;
	}
	catch (const std::exception& ex) {
		success = false;
		std::cout << "\n[end] video recording failed" << std::endl;
	}

	return success;
}