#include "performance.hpp"
#include <opencv2/imgproc.hpp>
#include <vector>
#include <algorithm>

double pfm_cvtcolor(const cv::Mat& src, const int loop_num)
{
	cv::TickMeter tm;
	std::vector<double> time;

	for (int i = 0; i <= loop_num; i++)
	{
		cv::Mat dst = cv::Mat(src.size(), CV_8UC1, cv::Scalar(0));
		tm.reset();
		tm.start();

		cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);

		tm.stop();
		time.push_back(tm.getTimeMilli());
	}
	std::sort(time.begin(), time.end());

	return time[loop_num / 2];
}

double pfm_hist(const cv::Mat& src, const int loop_num)
{
	cv::TickMeter tm;
	std::vector<double> time;

	std::vector<cv::Mat> planes;
	cv::split(src, planes);

	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true; bool accumulate = false;

	for (int i = 0; i <= loop_num; i++)
	{
		cv::Mat b_hist, g_hist, r_hist;
		tm.reset();
		tm.start();

		cv::calcHist(&planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
		cv::calcHist(&planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
		cv::calcHist(&planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

		tm.stop();
		time.push_back(tm.getTimeMilli());
	}

	std::sort(time.begin(), time.end());

	return time[loop_num / 2];
}

double pfm_median(const cv::Mat& src, const int loop_num)
{
	const int ksize = 5;

	cv::TickMeter tm;
	std::vector<double> time;

	for (int i = 0; i <= loop_num; i++)
	{
		cv::Mat dst = cv::Mat(src.size(), src.type(), cv::Scalar(0));
		tm.reset();
		tm.start();

		cv::medianBlur(src, dst, ksize);

		tm.stop();
		time.push_back(tm.getTimeMilli());
	}
	std::sort(time.begin(), time.end());

	return time[loop_num / 2];
}

double pfm_box(const cv::Mat& src, const int loop_num)
{
	const int ksize = 5;

	cv::TickMeter tm;
	std::vector<double> time;

	for (int i = 0; i <= loop_num; i++)
	{
		cv::Mat dst = cv::Mat(src.size(), src.type(), cv::Scalar(0));
		tm.reset();
		tm.start();

		cv::boxFilter(src, dst, -1, cv::Size(ksize, ksize));

		tm.stop();
		time.push_back(tm.getTimeMilli());
	}
	std::sort(time.begin(), time.end());

	return time[loop_num / 2];
}

double pfm_buildpyramid(const cv::Mat& src, const int loop_num)
{
	const int maxlevel = 5;

	cv::TickMeter tm;
	std::vector<double> time;

	for (int i = 0; i <= loop_num; i++)
	{
		std::vector<cv::Mat> pyramid;
		tm.reset();
		tm.start();

		cv::buildPyramid(src, pyramid, maxlevel);

		tm.stop();
		time.push_back(tm.getTimeMilli());
	}
	std::sort(time.begin(), time.end());

	return time[loop_num / 2];
}
