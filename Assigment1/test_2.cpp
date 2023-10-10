#include <opencv2/opencv.hpp>

using namespace cv;

int main(){

    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/lena.png");
    int w = img.cols;
    int h = img.rows;
    
    for(int ptr = 0; ptr < w * h; ptr++)
        img.data[ptr * 3] = 0;

    imshow("img", img);
    imwrite("ex1_3.png", img);
    waitKey(0);
    return 0;
}