#include <opencv2/opencv.hpp>
using namespace cv;
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/types_c.h>

int main(){

    Mat img(480, 640, CV_8UC3);

    img = CV_RGB(255, 255, 255);

    line(img, Point(10, 10), Point(100, 30), CV_RGB(255, 0, 0), 3, CV_AA);

    rectangle(img, Rect(30, 230, 120, 80), CV_RGB(0, 255, 0), -1);

    for (int r = 5; r < 120; r += 10){
        circle(img, Point(320, 240), r, CV_RGB(0, 0, r * 2), 3, CV_AA);
    }

    imshow("img", img);
    imwrite("ex2_1.png", img);

    waitKey(0);

    return 0;
}