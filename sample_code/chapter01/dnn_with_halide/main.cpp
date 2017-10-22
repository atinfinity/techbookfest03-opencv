#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<cv::Vec3b> readColors(const std::string &filename = "pascal-classes.txt");
void colorizeSegmentation(const cv::Mat &score, const std::vector<cv::Vec3b> &colors, cv::Mat &segm);

int main(int argc, char *argv[])
{
	const cv::String imageFile = (argc > 1) ? argv[1] : "rgb.jpg";

	cv::Mat img = cv::imread(imageFile, cv::IMREAD_COLOR);
	if (img.empty())
	{
		std::cerr << "Can't read image from the file: " << imageFile << std::endl;
		exit(-1);
	}
	cv::Size org_size = img.size();

	// Caffeモデルのインポート
	const std::string fcnType = "fcn8s";
	const cv::String modelTxt = fcnType + "-heavy-pascal.prototxt";
	const cv::String modelBin = fcnType + "-heavy-pascal.caffemodel";
	cv::Ptr<cv::dnn::Importer> importer;
	try
	{
		importer = cv::dnn::createCaffeImporter(modelTxt, modelBin);
	}
	catch (const cv::Exception &err)
	{
		std::cerr << err.msg << std::endl;
	}

	if (!importer)
	{
		std::cerr << "Can't load network by using the following files: " << std::endl;
		std::cerr << "prototxt:   " << modelTxt << std::endl;
		std::cerr << "caffemodel: " << modelBin << std::endl;
		std::cerr << fcnType << "-heavy-pascal.caffemodel can be downloaded here:" << std::endl;
		std::cerr << "http://dl.caffe.berkeleyvision.org/" << fcnType << "-heavy-pascal.caffemodel" << std::endl;
		exit(-1);
	}

	cv::dnn::Net net;
	importer->populateNet(net);
	importer.release();

	cv::resize(img, img, cv::Size(500, 500));
	cv::Mat inputBlob = cv::dnn::blobFromImage(img);

	net.setInput(inputBlob, "data");

	// dnnモジュールのバックエンドとしてHalideを指定する
	net.setPreferableBackend(cv::dnn::DNN_BACKEND_HALIDE);

	// dnnモジュールのターゲットとしてCPUを指定する
	net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

	cv::TickMeter tm;
	tm.start();
	cv::Mat score = net.forward("score");
	tm.stop();
	std::cout << "processing time: " << tm.getTimeMilli() << "ms." << std::endl;

	cv::Mat colorize, show, result;
	std::vector<cv::Vec3b> colors = readColors();
	colorizeSegmentation(score, colors, colorize);
	cv::addWeighted(img, 0.4, colorize, 0.6, 0.0, show);
	cv::resize(show, result, org_size);

	cv::imshow("Semantic Segmentation", result);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}

std::vector<cv::Vec3b> readColors(const std::string &filename)
{
	std::vector<cv::Vec3b> colors;

	std::ifstream fp(filename.c_str());
	if (!fp.is_open())
	{
		std::cerr << "File with colors not found: " << filename << std::endl;
		exit(-1);
	}

	std::string line;
	while (!fp.eof())
	{
		getline(fp, line);
		if (line.length())
		{
			std::stringstream ss(line);
			std::string name; ss >> name;
			int temp;
			cv::Vec3b color;
			ss >> temp; color[0] = (uchar)temp;
			ss >> temp; color[1] = (uchar)temp;
			ss >> temp; color[2] = (uchar)temp;
			colors.push_back(color);
		}
	}

	fp.close();
	return colors;
}

// Segmentation結果の描画
void colorizeSegmentation(const cv::Mat &score, const std::vector<cv::Vec3b> &colors, cv::Mat &segm)
{
	const int rows = score.size[2];
	const int cols = score.size[3];
	const int channels = score.size[1];

	cv::Mat maxCl(rows, cols, CV_8UC1);
	cv::Mat maxVal(rows, cols, CV_32FC1);
	for (int ch = 0; ch < channels; ch++)
	{
		for (int y = 0; y < rows; y++)
		{
			const float *ptrScore = score.ptr<float>(0, ch, y);
			uchar *ptrMaxCl = maxCl.ptr<uchar>(y);
			float *ptrMaxVal = maxVal.ptr<float>(y);
			for (int x = 0; x < cols; x++)
			{
				if (ptrScore[x] > ptrMaxVal[x])
				{
					ptrMaxVal[x] = ptrScore[x];
					ptrMaxCl[x] = (uchar)ch;
				}
			}
		}
	}

	segm.create(rows, cols, CV_8UC3);
	for (int y = 0; y < rows; y++)
	{
		const uchar *ptrMaxCl = maxCl.ptr<uchar>(y);
		cv::Vec3b *ptrSegm = segm.ptr<cv::Vec3b>(y);
		for (int x = 0; x < cols; x++)
		{
			ptrSegm[x] = colors[ptrMaxCl[x]];
		}
	}

}
