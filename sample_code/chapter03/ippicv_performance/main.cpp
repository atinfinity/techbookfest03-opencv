#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "common.hpp"
#include "performance.hpp"

int main(int argc, char *argv[])
{
	cv::Mat img = cv::imread("lena.jpg", cv::IMREAD_COLOR);
	if (img.empty())
	{
		std::cerr << "could not load image." << std::endl;
		return -1;
	}

	cv::Size sz[] = { sz1080p, sz2160p, sz4320p };
	const int loop_num = 10;

	for (int i = 0; i < 3; i++)
	{
		cv::Mat img_, gray_;
		cv::resize(img, img_, sz[i], -1, -1);
		std::cout << "image size = " << img_.size() << std::endl;

		double time = 0.0;
		time = pfm_cvtcolor(img_, loop_num);
		std::cout << "  cv::cvtColor = " << time << " ms." << std::endl;

		time = pfm_hist(img_, loop_num);
		std::cout << "  cv::calcHist = " << time << " ms." << std::endl;

		time = pfm_median(img_, loop_num);
		std::cout << "  cv::medianBlur = " << time << " ms." << std::endl;

		time = pfm_box(img_, loop_num);
		std::cout << "  cv::boxFilter = " << time << " ms." << std::endl;

		time = pfm_buildpyramid(img_, loop_num);
		std::cout << "  cv::buildPyramid = " << time << " ms." << std::endl;

		std::cout << std::endl;
	}

	return 0;
}

