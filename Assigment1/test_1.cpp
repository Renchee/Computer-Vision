#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;

int main(){

    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/lena.png");
    int w = img.cols;
    img.data[(128 + 128 * w) * 3] = 0;

    imshow("img", img);
    imwrite("ex1_2.png", img);
    waitKey(0);
    return 0; 
    }
