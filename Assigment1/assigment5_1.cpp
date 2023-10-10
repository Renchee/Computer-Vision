// 
// FLIP THE Myphoto
//

#include <opencv2/opencv.hpp>
#include <stdio.h>
using namespace cv;

void flip_lr(const Mat3b& src, Mat3b& dst){

    Mat3b _dst(src.rows, src.cols);
    for(int r = 0; r < _dst.rows; r++){
        for(int c = 0; c < _dst.cols; ++c){
            _dst(r, c) = src(r, src.cols -1 -c);
        }
    }
    dst = _dst;
}


int main(){

    Mat3b img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/myphoto.JPG");
    Mat3b resizeImg;
    resize(img, resizeImg, Size(520, 520));

    Mat3b flipped;
    flip(resizeImg, flipped, -1);
 
    imshow("OpenCv", flipped);
    
    waitKey(0);
    return 0;

}