#include <opencv2/core.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
	auto matrix = cv::Mat_<int>({ 0, -1, 0, -1, 5, -1, 0, -1, 0 }).reshape(1, 3);
	cv::Vec<uchar, 10> digits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	std::cout << "matrix = " << matrix << std::endl;
	std::cout << "digits = " << digits << std::endl;

	return 0;
}
