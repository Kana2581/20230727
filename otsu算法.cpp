#include <opencv2/opencv.hpp>
#include <cmath>
int main() {
	// 读取图像
	cv::Mat image = cv::imread("D:\Fig1039(a)(polymersomes).tif", cv::IMREAD_GRAYSCALE);

	if (image.empty()) {
		std::cout << "Error: Image not found or unable to read." << std::endl;
		return -1;
	}

	int width = image.cols;
	int height = image.rows;

	// 分割图像通道
	std::vector<cv::Mat> channels;
	cv::split(image, channels);

	// 统计直方图
	int histSize = 256;  // 直方图 bin 的数量
	float range[] = { 0, 256 };  // 像素值的范围
	const float* histRange = { range };
	bool uniform = true, accumulate = false;
	cv::Mat hist;
	std::vector<cv::Mat> histograms;

	for (const cv::Mat& channel : channels) {
		cv::calcHist(&channel, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);
		hist /= image.total();
		histograms.push_back(hist);
	}

	//积累累加和
	std::vector<double> p1;
	//积累累积均值
	std::vector<double> m;
	p1.push_back(histograms[0].at<float>(0));
	m.push_back(0);
	for (int j = 1; j < histSize; j++)
	{
		p1.push_back(histograms[0].at<float>(j)+p1[j-1]);
		m.push_back(p1[j]*j+m[j-1]);
	}
	int mg = m[255];
	std::vector<double> Qb;
	double Qg=0;
	int k=0;//otsu阈值k*
	int max= std::pow((mg*p1[0] - m[0]), 2.0) / (p1[0] * (1 - p1[0]));
	for (int j = 0; j < histSize; j++)
	{
		Qb.push_back(std::pow((mg*p1[j] - m[j]), 2.0) / (p1[j] * (1 - p1[j])));

		if ((int)Qb[j] > max)
		{
		
			max = Qb[j];
			k = j;
		}
	}




	cv::Mat image2(height, width, CV_8UC1);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			image2.at<uchar>(i, j) = (image.at<uchar>(i,j)>k) ? 255 : 0; // 将 true 映射为 255（白色），false 映射为 0（黑色）
		}
	}
	cv::imshow("Image from Bool Array", image2);

	// 等待按键
	cv::waitKey(0);

	

	return 0;
}