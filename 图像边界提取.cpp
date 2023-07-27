
#include <iostream>
#include <opencv2/opencv.hpp>


void erosion(bool ** input, bool ** output, int width, int height) {

	bool kernel[3][3] = {
		{true, true, true},
		{true, true, true},
		{true, true, true}
	};

	// 遍历图像像素
	for (int y = 1; y < height - 1; ++y) {
		for (int x = 1; x < width - 1; ++x) {

			bool isEroded = true;
			for (int ky = -1; ky <= 1; ++ky) {
				for (int kx = -1; kx <= 1; ++kx) {
					if (kernel[ky + 1][kx + 1] && !input[y + ky][x + kx]) {
						isEroded = false;
						break;
					}
				}
				if (!isEroded) {
					break;
				}
			}

			// 将腐蚀结果保存到临时数组中
			output[y][x] = isEroded;
		}
	}
}
void outputMatrix(bool ** output, int width, int height)
{
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			std::cout << (output[y][x] ? "1 " : "0 ");
		}
		std::cout << std::endl;
	}
}
bool isInputEquelsOutput(bool ** input, bool ** output, int width, int height)
{
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (input[y][x] != output[y][x])
				return false;
		}
	}
	return true;
}

void matrixsSub(bool ** input, bool ** output, int width, int height)
{
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			output[y][x] = input[y][x] - output[y][x];

		}
	}

}




int main() {
	// 读取图片
	cv::Mat image = cv::imread("D:/Fig0914(a)(licoln from penny).tif", cv::IMREAD_GRAYSCALE);

	if (image.empty()) {
		std::cout << "Failed to read the image." << std::endl;
		return 1;
	}

	// 获取图片大小
	int width = image.cols;
	int height = image.rows;

	// 将图像转换为 bool 数组
	bool** init = new bool*[height];
	for (int i = 0; i < height; ++i) {
		init[i] = new bool[width];
		for (int j = 0; j < width; ++j) {
			init[i][j] = (image.at<uchar>(i, j) != 0);
		}
	}




	bool** input = new bool*[height];
	for (int i = 0; i < height; i++)
	{
		input[i] = new bool[width];

		for (int j = 0; j < width; j++)
		{
			input[i][j] = init[i][j];
		}
	}

	bool** output = new bool*[height];
	for (int i = 0; i < height; ++i) {
		output[i] = new bool[width] {0};
	}


	erosion(input, output, width, height);





	cv::Mat image1(height, width, CV_8UC1);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			image1.at<uchar>(i, j) = output[i][j] ? 255 : 0; // 将 true 映射为 255（白色），false 映射为 0（黑色）
		}
	}

	cv::imshow("Image from Bool Array", image1);

	// 等待按键
	cv::waitKey(0);
	matrixsSub(input, output, width, height);
	cv::Mat image2(height, width, CV_8UC1);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			image2.at<uchar>(i, j) = output[i][j] ? 255 : 0; // 将 true 映射为 255（白色），false 映射为 0（黑色）
		}
	}

	cv::imshow("Image from Bool Array", image2);

	// 等待按键
	cv::waitKey(0);


	// 释放 bool 数组内存
	//for (int i = 0; i < height; ++i) {
	//	delete[] boolArray[i];
	//}
	//delete[] boolArray;

	return 0;
}