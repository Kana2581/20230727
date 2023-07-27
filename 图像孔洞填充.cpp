
#include <iostream>
#include <opencv2/opencv.hpp>

// 膨胀操作
void dilate(bool ** input, bool ** output, int width, int height) {
	// 定义膨胀的结构元素（3x3 十字形内核）
	bool kernel[3][3] = {
		{false, true, false},
		{true, true, true},
		{false, true, false}
	};

	// 遍历图像像素
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			// 初始化膨胀后的像素值为假（false）
			output[y][x] = false;

			// 遍历结构元素
			for (int ky = 0; ky < 3; ++ky) {
				for (int kx = 0; kx < 3; ++kx) {
					// 如果结构元素与图像对应位置重叠，进行膨胀操作
					if (y + ky - 1 >= 0 && y + ky - 1 < height&&x + kx - 1 >= 0 && x + kx - 1 < width)
					{
						if (kernel[ky][kx] && input[y + ky - 1][x + kx - 1]) {
							output[y][x] = true;
							break;
						}
					}
				}
				if (output[y][x]) {
					break;
				}
			}
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

void matrixsAnd(bool ** input, bool ** output, int width, int height)
{
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			output[y][x] = (input[y][x] && output[y][x]);

		}
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

int main() {
	// 读取图片
	cv::Mat image = cv::imread("D:/Fig0916(a).tif", cv::IMREAD_GRAYSCALE);

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



	bool** supplementary = new bool*[height];
	bool** input = new bool*[height];
	for (int i = 0; i < height; i++)
	{
		supplementary[i] = new bool[width];
		input[i] = new bool[width];

		for (int j = 0; j < width; j++)
		{
			supplementary[i][j] = !init[i][j];
			input[i][j] = 0;
		}
	}

	
	input[50][50] = 1;

	bool** output = new bool*[height];
	for (int i = 0; i < height; ++i) {
		output[i] = new bool[width];
	}


	while (true)
	{
		//outputMatrix(input, width, height);
	
		dilate(input, output, width, height);

		matrixsAnd(supplementary, output, width, height);


		if (isInputEquelsOutput(input, output, width, height))
			break;
		bool ** temp = output;
		output = new bool*[height];
		for (int i = 0; i < height; ++i) {
			output[i] = new bool[width];
		}
		for (int i = 0; i < height; ++i) {
			delete[] input[i];
		}
		input = temp;
	

	}


	cv::Mat image1(height, width, CV_8UC1);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			image1.at<uchar>(i, j) = input[i][j] ? 255 : 0; // 将 true 映射为 255（白色），false 映射为 0（黑色）
		}
	}

	cv::imshow("Image from Bool Array", image1);

	// 等待按键
	cv::waitKey(0);
	cv::Mat image2(height, width, CV_8UC1);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			image2.at<uchar>(i, j) = (input[i][j]||init[i][j]) ? 255 : 0; // 将 true 映射为 255（白色），false 映射为 0（黑色）
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