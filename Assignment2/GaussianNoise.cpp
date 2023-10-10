#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

using namespace cv;

// [-1, +1]のガウスノイズの生成
float Box_Muller() {

	float X, Y;
	X = (rand() % 10000) / 10000.0;
	Y = (rand() % 10000) / 10000.0;

	return sqrt(-2 * log(X)) * cos(2 * 3.14159 * Y);
}

// 画像にノイズを加える
void add_noise(Mat& img, Mat & out, float sigma) {
	// ガウスノイズを加える
        img.copyTo(out);
	for (int ptr = 0; ptr < 3 * img.cols * img.rows; ptr++) {
		int v = img.data[ptr] + Box_Muller() * sigma;
		if (v < 0)v = 0;
		if (v > 255)v = 255;
		out.data[ptr] = v;
	}
}

int main(){

    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/Assigment1/myphoto.JPG");

    resize(img, img, Size(800, 800 * img.rows / img.cols));

    float sigma = 30.0;
    Mat out;

    add_noise(img, out, sigma);

    imshow("input", img);
    imshow("addGaussianNoise", out);
    imwrite("addGaussianNoise.jpg", out);

    waitKey(0);
}
