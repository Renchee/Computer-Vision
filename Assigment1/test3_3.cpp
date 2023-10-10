#include <opencv2/opencv.hpp>
using namespace cv;

// ヒストグラム計算＆平均値を返す
float calc_histgram(const Mat & img, float *hist) {

    float wh = img.cols * img.rows;



    memset(hist, 0, sizeof(float) * 256);
    // 全画素をスキャンして、ヒストグラム加算
    for (int ptr = 0; ptr < wh; ptr++)
   	 hist[img.data[ptr]]++;

    // [0, 1]の範囲に正規化
    float average = 0;
    for (int i = 0; i < 256; i++) {
   	 hist[i] /= float(wh);
   	 average += i * hist[i];
    }

    return average;
}


int main(){

    // 画像を読み込む
    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/in.jpg");
    Mat ref_img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/ref.jpg");
    std::vector<Mat> rgb, ref_rgb;
    split(img, rgb);
    split(ref_img, ref_rgb);
    // ヒストグラム計算
    float hist[3][256], ref_hist[3][256];
    float ave[3], ref_ave[3];
    float gain[3];
    for(int i = 0;i < 3;i++){
   	 // チャンネルごとの平均画素値を計算
   	 ave[i] = calc_histgram(rgb[i], hist[i]);
   	 ref_ave[i] = calc_histgram(ref_rgb[i], ref_hist[i]);
   	 // リファレンス画像からゲインを決定
   	 gain[i] = ref_ave[i] / ave[i];
   	 // ゲインを掛ける
   	 rgb[i] = rgb[i] * gain[i];
    }
    Mat out;
    merge(rgb, out);
    // 画像表示・保存
    imshow("in", img);
    imshow("out", out);
    imshow("ref", ref_img);
    imwrite("ex3_3.png", out);
    waitKey(0);

    return 0;
}
