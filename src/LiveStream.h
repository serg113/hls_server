#pragma once
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>


class LiveStream
{
public:
	LiveStream(const std::string& lilveStreamUrl);

	void saveFramesAsJpeg(const std::string& jpegFolder) const;
	void saveFramesAsVideo(const std::string& videoFolder) const;

private:
	std::unique_ptr<cv::VideoCapture> openStream() const;
	void saveAsJpeg(std::unique_ptr<cv::VideoCapture> stream, const std::string& jpegFolder) const;
	void saveAsMp4(std::unique_ptr<cv::VideoCapture> stream, const std::string& jpegFolder) const;

	std::string generateImageName(const std::string& jpegFolder, size_t index) const;
	std::string generateVideoName(const std::string& jpegFolder, size_t index) const;

	std::string liveStreamUrl_;

};