#include "NetworkService.h"
#include "LiveStream.h"
#include "utils.h"
#include "tests.h"

#include <iostream>
#include <string>
#include <exception>

// only checking valid cases implemented


void runAllTests() {};

void testSocket()
{
	try {
		NetworkService service;
		service.waitConnectionFromTrustedDomains({ "127.0.0.1", "192.168.99.1" });
		if (service.connectionEstablishedAndAuthenticated({ {"root", "hash777"} }))
			std::cout << "connection test passed" << std::endl;
		
	}
	catch (const std::exception & ex)
	{
		std::cout << "connection test failed" << std::endl;
	}
	
}

void testLiveStream()
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