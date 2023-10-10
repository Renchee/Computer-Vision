#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;

int main(){

    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/lena.png");
    imshow("img", img);
    imwrite("ex1.png", img);
    waitKey(0);
    return 0; 
    }
