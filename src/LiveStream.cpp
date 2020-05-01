#include "LiveStream.h"
#include <opencv2/opencv.hpp>
#include <stdexcept>

LiveStream::LiveStream(const std::string& liveStreamUrl) : liveStreamUrl_(liveStreamUrl)
{ };


void LiveStream::saveFramesAsJpeg(const std::string& jpegFolder) const
{
	auto stream = openStream();
	saveAsJpeg(stream, jpegFolder);
}

void LiveStream::saveFramesAsVideo(const std::string& videoFolder) const
{
	auto stream = openStream();
	saveAsMp4(stream, videoFolder);
}

cv::VideoCapture LiveStream::openStream() const
{
	cv::VideoCapture stream(liveStreamUrl_);

	if (!stream.isOpened()) {
		throw std::runtime_error("cannot open live stream");
	}
	return stream;
}

void LiveStream::saveAsJpeg(cv::VideoCapture& stream, const std::string& jpegFolder) const

{
	cv::Mat frame;

	for (size_t i = 0; i < 100; ++i) { // for cycle is for testing purposes
		if (!stream.read(frame)) {
			throw std::runtime_error("cannot read frame");
		}
		std::string imageName = generateImageName(jpegFolder, i);
		cv::imwrite(imageName, frame);
	}
}

void LiveStream::saveAsMp4(cv::VideoCapture& stream, const std::string& videoFolder) const
{
	auto writer = cv::VideoWriter(
		generateVideoName(videoFolder, 1), 
		cv::VideoWriter::fourcc('m', 'p', '4', 'v'), 
		stream.get(cv::CAP_PROP_FPS), 
		cv::Size(stream.get(cv::CAP_PROP_FRAME_WIDTH), stream.get(cv::CAP_PROP_FRAME_HEIGHT)));

	cv::Mat frame;
	for (size_t i = 0; i < 100; ++i){
		if (!stream.read(frame)) {
			throw std::runtime_error("cannot read frame");
		}
		writer.write(frame);
	}
}

std::string LiveStream::generateImageName(const std::string& jpegFolder, size_t index) const
{
	return jpegFolder + "lsPic_" + std::to_string(index) + ".jpg";
}

std::string LiveStream::generateVideoName(const std::string& videoFolder, size_t index) const
{
	return videoFolder + "lsVid_" + std::to_string(index) + ".mp4";
}

