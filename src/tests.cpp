
#include "LiveStream.h"
#include "tests.h"

#include <iostream>
#include <string>
#include <exception>

// only checking valid cases implemented

void runAllTests()
{
	std::cout << "test 1/3 --> creating live stream   : ";
	testCreatingLiveStream() ? 	std::cout << "passed\n" : std::cout << "failed\n";

	std::cout << "test 2/3 --> saving stream as jpeg  : ";
	testSavingLiveStreamAsJpeg() ? std::cout << "passed\n" : std::cout << "failed\n";

	std::cout << "test 3/3 --> saving stream as video : ";
	testSavingLiveStreamAsVideo() ? std::cout << "passed\n" : std::cout << "failed\n";
}

bool testCreatingLiveStream()
{
	bool success = true;

	try {
		auto stream = createLiveStream("http://192.168.99.1:8000/media/live");
	}
	catch (const std::exception& ex){
		success = false;
	}

	return success;
}

bool testSavingLiveStreamAsJpeg()
{
	bool success = true;

	try {
		auto stream = createLiveStream("http://192.168.99.1:8000/media/live");
		stream->saveFramesAsJpeg("./media/jpeg/");
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
		auto stream = createLiveStream("http://192.168.99.1:8000/media/live");
		stream->saveFramesAsVideo("./media/video/");
	}
	catch (const std::exception& ex) {
		success = false;
	}

	return success;
}