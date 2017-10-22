#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
	cv::Mat_<uchar> img1 = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);
	if (img1.empty())
	{
		std::cerr << "could not load image." << std::endl;
		return -1;
	}

	cv::Mat_<uchar> img2;
	img1.copyTo(img2);

	// 従来のアクセス方法
	for (int y = 0; y < img1.rows; y++)
	{
		for (int x = 0; x < img1.cols; x++)
		{
			// 画素の反転
			img1.ptr<uchar>(y)[x] = 255 - img1.ptr<uchar>(y)[x];
		}
	}

	// C++11 styleのアクセス方法
	for (auto& pixel : img2)
	{
		// 画素の反転
		pixel = 255 - pixel;
	}

	cv::imshow("img1", img1);
	cv::imshow("img2", img2);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}
