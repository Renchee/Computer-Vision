#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

using namespace cv;

int main(){
    
    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/Assigment1/myphoto.JPG");
    resize(img, img, Size(800, 800 * img.rows / img.cols));

    Mat out;
    Mat h(11, 11, CV_64F);
    h = 1.0 / (11.0 * 11.0);
    filter2D(img, out, 8, h);

    imshow("input", img);
    imshow("output", out);

    imwrite("OpenCV_Standart_filter.jpg", out);

    waitKey(0); 
}