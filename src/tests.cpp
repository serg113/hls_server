#include "NetworkService.h"
#include "LiveStream.h"
#include "utils.h"
#include "tests.h"

#include <iostream>
#include <string>
#include <exception>

#include <boost/beast/core/detail/base64.hpp>


// only checking valid cases implemented

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
		NetworkService service;
		service.waitConnectionFromTrustedDomains({ "127.0.0.1", "192.168.99.1" });
		
		std::cout << "hlsService running ... port 7070, localhost" << std::endl;

		if (service.connectionIsAuthenticated({ {"root", "cm9vdDEyMzQ1NgDMzMzMzA=="} })) // root123456
		{
			if (service.routPathEquals("/frames"))
				std::cout << "routing passed from user: /frames" << std::endl;
			if (service.routPathEquals("/record"))
				std::cout << "routing passed from user: /record" << std::endl;

			std::cout << "live link is : " << service.liveStreamUrl() << std::endl;

			std::cout << "connection test passed" << std::endl;
		}
	}
	catch (const std::exception & ex)
	{
		std::cout << "connection test failed" << std::endl;
	}
	
}

void testLiveStreamProcessing()
{
	std::cout << "test 1/2 --> saving stream as jpeg  : ";
	testSavingLiveStreamAsJpeg() ? std::cout << "passed\n" : std::cout << "failed\n";
	
	std::cout << "test 2/2 --> saving stream as video : ";
	testSavingLiveStreamAsVideo() ? std::cout << "passed\n" : std::cout << "failed\n";
}


bool testSavingLiveStreamAsJpeg()
{
	bool success = true;

	try {
		LiveStream stream("http://192.168.99.1:8000/media/live");
		createFolderIfNotExist("./media/jpeg/");
		stream.saveFramesAsJpeg("./media/jpeg/");
	}
	catch (const std::exception& ex) {
		success = false;
	}

	return success;
}

bool testSavingLiveStreamAsVideo()
{
	bool success = true;

	try {
		LiveStream stream("http://192.168.99.1:8000/media/live");
		createFolderIfNotExist("./media/video/");
		stream.saveFramesAsVideo("./media/video/");
	}
	catch (const std::exception& ex) {
		success = false;
	}

	return success;
}
