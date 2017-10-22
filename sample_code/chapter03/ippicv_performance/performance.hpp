#pragma once
#include <opencv2/core.hpp>

double pfm_cvtcolor(const cv::Mat& src, const int loop_num);
double pfm_hist(const cv::Mat& src, const int loop_num);
double pfm_median(const cv::Mat& src, const int loop_num);
double pfm_box(const cv::Mat& src, const int loop_num);
double pfm_buildpyramid(const cv::Mat& src, const int loop_num);

