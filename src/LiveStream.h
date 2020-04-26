#pragma once

#include <string>


class LiveStream
{
public:
	LiveStream* init(const std::string& lilveStreamUrl);

	void saveFramesAsJpeg(const std::string& jpegFolder) const;
	void saveFramesAsVideo(const std::string& videoFolder) const;

};



LiveStream* createLiveStream(const std::string& lilveStreamUrl);
