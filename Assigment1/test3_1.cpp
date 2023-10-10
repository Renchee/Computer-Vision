#include <opencv2/opencv.hpp>
using namespace cv;

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

int main(){

    // 画像を読み込む
    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/lena.png");
    // 適当にゲインをかけてオフセットを足す
/*    for (int ptr = 0; ptr < 3 * img.cols * img.rows; ptr++)
       	img.data[ptr] = max(min(img.data[ptr] * 1.5 - 64, 255), 0);
    // 画像表示・保存
    imshow("img", img);
    imwrite("ex3_1.png", img); */

        // ガンマ補正
    float gamma = 2.2;
    for (int ptr = 0; ptr < 3 * img.cols * img.rows; ptr++)
        img.data[ptr] = max(min(255*pow(img.data[ptr] / 255.0, 1.0 / gamma), 255), 0);
    
    imshow("img", img);
    waitKey(0);

    return 0;
}