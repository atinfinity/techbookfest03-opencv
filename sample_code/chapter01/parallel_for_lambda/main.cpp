#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <complex>
#include <iostream>

int mandelbrot(const std::complex<float>& z0, const int max)
{
	std::complex<float> z = z0;
	for (int t = 0; t < max; t++)
	{
		if (z.real()*z.real() + z.imag()*z.imag() > 4.0f) return t;
		z = z*z + z0;
	}
	return max;
}

int mandelbrotFormula(const std::complex<float>& z0, const int maxIter = 500) {
	int value = mandelbrot(z0, maxIter);
	if ((maxIter) - value == 0)
	{
		return 0;
	}
	return cvRound(sqrt(value / (float)maxIter) * 255);
}

int main(int argc, char *argv[])
{
	cv::Mat mandelbrotImg(cv::Size(640, 480), CV_8U);

	const float x1 = -2.1f, x2 = 0.6f;
	const float y1 = -1.2f, y2 = 1.2f;
	const float scaleX = mandelbrotImg.cols / (x2 - x1);
	const float scaleY = mandelbrotImg.rows / (y2 - y1);

	cv::parallel_for_(cv::Range(0, mandelbrotImg.rows*mandelbrotImg.cols), [&](const cv::Range& range)
	{
		for (int r = range.start; r < range.end; r++)
		{
			int y = r / mandelbrotImg.cols;
			int x = r % mandelbrotImg.cols;
			float x0 = x / scaleX + x1;
			float y0 = y / scaleY + y1;
			std::complex<float> z0(x0, y0);
			uchar value = (uchar)mandelbrotFormula(z0);
			mandelbrotImg.ptr<uchar>(y)[x] = value;
		}
	});

	cv::imshow("Mandelbrot", mandelbrotImg);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}
