#include <opencv2/opencv.hpp>
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


void mymedian(Mat& in, Mat& out, int N) {
	int w, h;
	w = in.cols; h = in.rows;

	int M = (N - 1) / 2;
	out = Mat(h, w, CV_8UC3);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {

			std::vector<unsigned char> r, g, b;

			for (int sy = -M; sy <= M; sy++) {
				int ty = y + sy;
				if (ty < 0)ty = -ty; else if (ty >= h) ty = h - 1 - (h - sy);
				for (int sx = -M; sx <= M; sx++) {
					int tx = x + sx;
					if (tx < 0)tx = -tx; else if (tx >= w) tx = w - 1 - (w - sx);
					Vec3b & p = in.at<Vec3b>(ty, tx);
					b.push_back(p[0]);
					g.push_back(p[1]);
					r.push_back(p[2]);
				} //sx
			}//sy
			sort(b.begin(), b.end());
			sort(g.begin(), g.end());
			sort(r.begin(), r.end());
			int med = floor((N * N) / 2);
			out.at<Vec3b>(y, x) = Vec3b(b[med], g[med], r[med]);

		}// x    
	}//y
}

int main() {

	Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/Assigment1/myphoto.JPG");

	resize(img, img, Size(800, 800 * img.rows / img.cols));

	// ゴマ塩ノイズを加える
	for (int i = 0; i < 10000; i++) {
		int ry = rand() % img.rows;
		int rx = rand() % img.cols;
		img.at<Vec3b>(ry, rx) = Vec3b(255,255,255);
	}

	// フィルタをかける
	Mat ava, med;
	Mat h(3, 3, CV_64F);
	h = 1.0 / (3.0 * 3.0);

	myfilter2D(img, ava, h);
	mymedian(img, med, 3);
	// 結果表示：jpgだと劣化が入るのでpngで
	imshow("in", img);
	imshow("ava", ava);
	imshow("med", med);
	imwrite("in.png", img);
	imwrite("ava.png", ava);
	imwrite("med.png", med);

	waitKey(0);
}
