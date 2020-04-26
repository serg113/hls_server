#include "LiveStream.h"


LiveStream* LiveStream::init(const std::string& lilveStreamUrl)
{
	// init opencv strem
	return this;
}


void LiveStream::saveFramesAsJpeg(const std::string& jpegFolder) const
{
	// save files and throw exception at failure
}

void LiveStream::saveFramesAsVideo(const std::string& videoFolder) const
{
	// save files and throw exception at failure
}


LiveStream* createLiveStream(const std::string& lilveStreamUrl)
{
	return (new LiveStream())->init(lilveStreamUrl);
}
