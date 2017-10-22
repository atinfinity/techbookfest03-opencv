#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
	cv::Mat img(cv::Size(512, 512), CV_8UC1);
	std::cout << "img.cols: " << img.cols << std::endl;
	std::cout << "img.rows: " << img.rows << std::endl;
	std::cout << "img.size: " << img.size() << std::endl;
	std::cout << "img.step: " << img.step << std::endl;
	std::cout << "img.isContinuous(): " << img.isContinuous() << std::endl << std::endl;

	cv::cuda::GpuMat d_img(img);
	std::cout << "d_img.cols: " << d_img.cols << std::endl;
	std::cout << "d_img.rows: " << d_img.rows << std::endl;
	std::cout << "d_img.size: " << d_img.size() << std::endl;
	std::cout << "d_img.step: " << d_img.step << std::endl;
	std::cout << "d_img.isContinuous(): " << d_img.isContinuous() << std::endl;

	std::cout << "---------------" << std::endl;

	cv::Mat img2(cv::Size(100, 100), CV_8UC1);
	std::cout << "img2.cols: " << img2.cols << std::endl;
	std::cout << "img2.rows: " << img2.rows << std::endl;
	std::cout << "img2.size: " << img2.size() << std::endl;
	std::cout << "img2.step: " << img2.step << std::endl;
	std::cout << "img2.isContinuous(): " << img2.isContinuous() << std::endl << std::endl;

	cv::cuda::GpuMat d_img2(img2);
	std::cout << "d_img2.cols: " << d_img2.cols << std::endl;
	std::cout << "d_img2.rows: " << d_img2.rows << std::endl;
	std::cout << "d_img2.size: " << d_img2.size() << std::endl;
	std::cout << "d_img2.step: " << d_img2.step << std::endl;
	std::cout << "d_img2.isContinuous(): " << d_img2.isContinuous() << std::endl;

	return 0;
}

