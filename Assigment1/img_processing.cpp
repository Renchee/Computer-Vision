#include <opencv2/opencv.hpp>

using namespace cv;

void proc(const Mat& img, Mat& out) {
	int w = img.cols, h = img.rows;
 
	img.copyTo(out);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			Vec3b& p = out.at<Vec3b>(y, x);
			p = p * 0.5;
			p[1] = 0;
		}
	}
	for(int i = 0;i < 100;i++)
		circle(out, Point(rand()%w, rand()%h), 10, CV_RGB(rand()%255, rand() % 255, rand() % 255) , -1, LINE_AA);

	rectangle(out, Rect(150,100, 200, 100), CV_RGB(255,0,0), -1, LINE_AA);

	for (int x = 0; x < w; x += 100)
		line(out, Point(x, 0), Point(x, h), CV_RGB(0,255,0), 1, LINE_AA);

	for (int y = 0; y < h; y += 100)
		line(out, Point(0, y), Point(w, y), CV_RGB(0, 255, 0), 1, LINE_AA);

	putText(out, "Test", Point(30, 130), FONT_HERSHEY_SCRIPT_SIMPLEX, 3.0, CV_RGB(255,255,0), 3.0, LINE_AA);
}
int main(int argc, char* argv[]) {

	Mat img, out;

	VideoCapture cap(0);
	while (1) {
		cap >> img;
		imshow("img", img);

		proc(img, out);

		imshow("out", out);
		waitKey(1);
	}
}
