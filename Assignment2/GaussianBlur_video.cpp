#include <opencv2/opencv.hpp>

using namespace cv;


int main(int argc, char* argv[]) {
    Mat img, out;
    VideoCapture cap(0);
    int count = 0;
    while (1) {
        cap >> img;
        imshow("img", img);

        float sigma = 4 + 4 * sin(count/ 10.0);
        int N = 2 * floor(sigma * 3) + 1;
        GaussianBlur(img, out, Size(N, N), sigma);
        count++;

        imshow("out", out);
        waitKey(1);
    }
}