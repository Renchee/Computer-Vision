#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/types_c.h>

using namespace cv;


void myGaussianfilter(Mat & in, Mat & out, Mat & f){
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

    float sigma = 3.0;
    int N = floor(sigma * 3.0) * 2 + 1;
    Mat h(N, N, CV_64F);

    double sum = 0;

    for (int sy = 0; sy < N; sy++){
        for (int sx = 0; sx < N; sx++){
            int x = sx - (N - 1) / 2;
            int y = sy - (N - 1) / 2;
            double g = exp(-(x * x + y * y) / (2.0 * sigma * sigma)) / (2 * 3.14159 * sigma * sigma);
            h.at<double>(sy, sx) = g;
            sum += g;
        }
    }

    h = h * (1 / sum);

    Mat out;
    myGaussianfilter(img, out, h);


    imshow("in", img);
    imshow("out", out);
    imwrite("gaussianOut.jpg", out);

    waitKey(0);
    return 0;
}