#include <opencv2/opencv.hpp>

using namespace cv;

void calc_histogram(const Mat & img, float *hist) {

    float wh = img.cols * img.rows;

    memset(hist, 0, sizeof(float) * 256);

    for (int ptr = 0; ptr < wh; ptr++)
        hist[img.data[ptr]]++;

    for (int i = 0; i < 256; i++)
        hist[i] /= float(wh);
    
}

void draw_histogram(Mat & img, float *hist, Scalar col) {

    for (int i = 0; i < 256; i++) {
        line(img, Point(i, 256), Point(i, 256 - 10000 * hist[i]), col);
    }
}

int main(){

    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/lena.png", 0);

    float hist[256];
    calc_histogram(img, hist);

    draw_histogram(img, hist, CV_RGB(128, 128, 128));

    imshow("img", img);
    waitKey(0);

    return 0;
}