#include <iostream>

// 腐蚀操作
void erosion(bool ** input, bool ** output, int width, int height) {
	// 定义腐蚀的结构元素（3x3 内核）
	bool kernel[3][3] = {
		{true, true, true},
		{true, true, true},
		{true, true, true}
	};

	// 遍历图像像素
	for (int y = 1; y < height-1; ++y) {
		for (int x = 1; x < width-1; ++x) {
			
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
	const int width = 10;
	const int height = 5;

	// 原始图像
	bool init[height][width] = {
		{1,1,1,0,1,1,1,1,1,0},
		{1,1,1,0,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1}

	};

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

	// 执行腐蚀操作

	erosion(input, output, width, height);
	std::cout <<"A腐蚀B"<< std::endl;
	outputMatrix(output, width, height);
	std::cout << std::endl;
	std::cout << "b(A)=A-(A腐蚀B)" << std::endl;
	matrixsSub(input, output, width, height);
	outputMatrix(output, width, height);
	



	return 0;
}
