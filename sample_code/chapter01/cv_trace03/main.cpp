#include <opencv2/core.hpp>

// プロファイリング機能を使うために必要なヘッダファイル
#include <opencv2/core/utils/trace.hpp>

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

void processImage(const cv::Mat& img, cv::Mat& bin)
{
	// 任意の関数の実行区間にラベル付けする
	CV_TRACE_FUNCTION();

	cv::Mat gray;
	cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
	cv::threshold(gray, bin, 128, 255, cv::THRESH_BINARY);
}

int main(int argc, char *argv[])
{
	cv::Mat img = cv::imread("lena.jpg", cv::IMREAD_COLOR);
	if (img.empty())
	{
		std::cerr << "could not load image." << std::endl;
		return -1;
	}

	cv::Mat bin;
	processImage(img, bin);

	return 0;
}
