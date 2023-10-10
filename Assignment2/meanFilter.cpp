#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/types_c.h>

using namespace cv;

void myfilter2D(Mat & in, Mat & out, Mat & f){
    int w, h, fw, fh;
    w = in.cols; h = in.rows;
    fw = f.cols; fh = f.rows;

    if (fw != fh || fw % 2 == 0) return;

    int N = (fw - 1) / 2;
    out = Mat(h, w, CV_8UC3);
    for (int y = N; y < h - N; y++){
        for (int x = N; x < w - N; x++){

            Vec3b p = 0;

            for (int sy =  -N; sy <= N; sy++){
                for (int sx = -N; sx <= N; sx++){
                    p = p + in.at<Vec3b>(sy + y, sx + x) * f.at<double>(sy + N, sx + N);
                }
            }

            out.at<Vec3b>(y,x) = p;
        }
    }
}

int main(){

    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/Assigment1/myphoto.JPG");

    resize(img, img, Size(800, 800 * img.rows / img.cols));

    Mat h = (Mat_<double>(3,3) <<
            1 / 9.0, 1 / 9.0, 1 / 9.0,
            1 / 9.0, 1 / 9.0, 1 / 9.0,
            1 / 9.0, 1 / 9.0, 1 / 9.0);

    Mat out;
    myfilter2D(img, out, h);

    imshow("in", img);
    imshow("out", out);
    imwrite("meanOut.jpg",out);

    waitKey(0);
    return 0;
}