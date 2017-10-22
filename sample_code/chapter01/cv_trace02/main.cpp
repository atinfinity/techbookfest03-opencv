#include <opencv2/core.hpp>

// プロファイリング機能を使うために必要なヘッダファイル
#include <opencv2/core/utils/trace.hpp>

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
	cv::Mat img = cv::imread("lena.jpg", cv::IMREAD_COLOR);
	if (img.empty())
	{
		std::cerr << "could not load image." << std::endl;
		return -1;
	}

	cv::Mat gray, bin;

	CV_TRACE_REGION("convert");
	cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

	CV_TRACE_REGION_NEXT("threshold");
	cv::threshold(gray, bin, 128, 255, cv::THRESH_BINARY);

	return 0;
}
