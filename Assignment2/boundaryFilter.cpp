#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

using namespace cv;


void myfilter2D(Mat& in, Mat& out, Mat& f) {
	int w, h, fw, fh;
	w = in.cols; h = in.rows;
	fw = f.cols; fh = f.rows;

	if (fw != fh || fw % 2 == 0)return;

	int N = (fw - 1) / 2;
	out = Mat(h, w, CV_8UC3);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {

			Vec3f p = 0;

			for (int sy = -N; sy <= N; sy++) {
				int ty = y + sy;
				if (ty < 0)ty = -ty; else if (ty >= h) ty = h - 1 - (h - sy);
				for (int sx = -N; sx <= N; sx++) {
					int tx = x + sx;
					if (tx < 0)tx = -tx; else if (tx >= w) tx = w - 1 - (w - sx);
					p = p + (Vec3f)in.at<Vec3b>(ty, tx) * f.at<double>(sy + N, sx + N);
				} //sx
			}//sy

			out.at<Vec3b>(y, x) = p;

		}// x    
	}//y
}

int main(){

    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/Assigment1/myphoto.JPG");

    resize(img, img, Size(800, 800 * img.rows / img.cols));

    Mat h(11, 11, CV_64F);
    h = 1.0 / (11.0 * 11.0);

    Mat out;
    myfilter2D(img, out, h);

    imshow("in", img);
    imshow("out", out);

    waitKey(0);
    return 0;
}