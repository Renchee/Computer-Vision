#include <opencv2/opencv.hpp>
using namespace cv;

// ヒストグラム計算
void calc_histogram(const Mat & img, float *hist) {

    float wh = img.cols * img.rows;

    memset(hist, 0, sizeof(float) * 256);
    // 全画素をスキャンして、ヒストグラム加算
    for (int ptr = 0; ptr < wh; ptr++)
   	 hist[img.data[ptr]]++;

    // [0, 1]の範囲に正規化
    for (int i = 0; i < 256; i++)
   	 hist[i] /= float(wh);
}

// ヒストグラム描画
void draw_histogram(Mat & img,float *hist,  Scalar col, int dx) {

    for (int i = 0; i < 256; i+=5) {
   	 line(img, Point(i+dx, 256), Point(i+dx, 256 - 10000 * hist[i]), col);
    }
}

int main(){

    // 画像を読み込む
    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/lena.png");
    std::vector<Mat> rgb;
    // チャンネル分解
    split(img, rgb);
    // ヒストグラムを計算
    float hist[3][256];
    for(int i = 0;i < 3;i++)
   	 calc_histogram(rgb[i], hist[i]);
    // ヒストグラム描画
    draw_histogram(img, hist[0], CV_RGB(0,0,255),   0);
    draw_histogram(img, hist[1], CV_RGB(0, 255, 0), 1);
    draw_histogram(img, hist[2], CV_RGB(255, 0, 0), 2);
    // 画像表示・保存
    imshow("img", img);
    imwrite("ex2_3.png", img);
    waitKey(0);

    return 0;

}