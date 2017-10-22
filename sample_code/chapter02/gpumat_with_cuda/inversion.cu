#include <opencv2/core.hpp>
#include <opencv2/core/cuda/common.hpp>
#include <opencv2/cudev/common.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

// CUDAカーネル
__global__ void inversionGpu
(
	const cv::cuda::PtrStepSz<uchar> src,
	cv::cuda::PtrStepSz<uchar> dst
)
{
	const int x = blockDim.x * blockIdx.x + threadIdx.x;
	const int y = blockDim.y * blockIdx.y + threadIdx.y;
	if((y >= 0) && (y < src.rows))
	{
		if((x >= 0) && (x < src.cols))
		{
			dst.ptr(y)[x] = (255 - src.ptr(y)[x]);
		}
	}
}

void launchInversionGpu
(
	cv::cuda::GpuMat& src,
	cv::cuda::GpuMat& dst
)
{
	const dim3 block(32, 32);
	const dim3 grid(cv::cudev::divUp(dst.cols, block.x), cv::cudev::divUp(dst.rows, block.y));

	// CUDAカーネル起動
	inversionGpu<<<grid, block>>>(src, dst);

	CV_CUDEV_SAFE_CALL(cudaGetLastError());
	CV_CUDEV_SAFE_CALL(cudaDeviceSynchronize());
}

int main(int argc, char *argv[])
{
	cv::Mat src = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);
	if (src.empty())
	{
		std::cerr << "could not load image." << std::endl;
		return -1;
	}

	cv::cuda::GpuMat d_src(src);
	cv::cuda::GpuMat d_dst(d_src.size(), d_src.type());
	launchInversionGpu(d_src, d_dst);

	cv::Mat dst;
	d_dst.download(dst);

	cv::imshow("dst", dst);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}
