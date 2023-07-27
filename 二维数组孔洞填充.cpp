#include <iostream>

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
void outputMatrix(bool ** output,int width,int height)
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

void matrixsAnd(bool ** input, bool ** output, int width, int height) 
{
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			output[y][x] = (input[y][x] && output[y][x]);
				
		}
	}

}
int main() {
	const int width = 7;
	const int height = 10;

	// 原始图像
	bool init[height][width] = {
		{0,0,0,0,0,0,0},
		{0,0,1,1,0,0,0},
		{0,1,0,0,1,0,0},
		{0,1,0,0,1,0,0},
		{0,0,1,0,1,0,0},
		{0,0,1,0,1,0,0},
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,1,1,1,0,0},
		{0, 0, 0, 0, 0,0,0},

	};

	bool** supplementary = new bool*[height];
	bool** input=new bool*[height];
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
	// 膨胀后的图像
	input[2][2] = 1;
	bool** output = new bool*[height];
	for (int i = 0; i < height; ++i) {
		output[i] = new bool[width];
	}

	// 执行膨胀操作
	int i = 0;
	while (true)
	{
		std::cout << "X" << i++ << std::endl;
		outputMatrix(input, width, height);
		dilate(input, output, width, height);
	
		matrixsAnd(supplementary, output,width,height);
	
		
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
		std::cout << std::endl;

	}


	// 输出膨胀后的图像
	


	return 0;
}
