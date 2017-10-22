#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
	cv::Mat img = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);
	if (img.empty())
	{
		std::cerr << "could not load image." << std::endl;
		return -1;
	}

	cv::cuda::GpuMat d_img(img);
	cv::cuda::flip(d_img, d_img, 0);

	cv::Mat dst(d_img);
	cv::imshow("gpu_flip", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}
