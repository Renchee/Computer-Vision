//

#include <opencv2/opencv.hpp>
#include <stdio.h>
using namespace cv;

int main(){

    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/myphoto.JPG");
    
    int w = img.cols, h = img.rows;
    int sw = 800, sh = 800 * h / w;

    resize(img, img, Size(sw, sh));
    
    for(int y = 0; y < sh; y++){
        for(int x = 0; x < sw; x++){
            Vec3b& p = img.at<Vec3b>(y, x);
            p = p * 0.5;
            p[1] = 0;
        }
    }
    imshow("Img", img);
    
    waitKey(0);
    return 0;

}