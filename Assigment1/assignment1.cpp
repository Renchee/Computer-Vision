#include <opencv2/opencv.hpp>

using namespace cv;

void draw_rectangle(Mat img) {
	int w = img.cols, h = img.rows;
    int sw = 800, sh = 800 * h / w;

    resize(img, img, Size(sw, sh)); 

   for (int y = 0; y < sh; y+=sh/5 ){
        
        for (int x = 0; x < sw; x+=sw/5 ){

            rectangle(img, Rect(y, x, sw/10, sh/10), CV_RGB(0, 255, 0), -1, LINE_AA);
            rectangle(img, Rect(y+sh/10, x+sw/10, sw/10, sh/10), CV_RGB(0, 255, 0), -1, LINE_AA);

        }
   }

   putText(img, "235-d8906", Point(0, 60), FONT_HERSHEY_SIMPLEX, 1.2, CV_RGB(255,0,0), 1.0, LINE_AA);
   imshow("output", img);
   imwrite("out.jpg", img);
}
int main(int argc, char* argv[]) {

    Mat img = imread("//Users/renchinsuren/Documents/2023B/Computer Vision/Assigment1/myphoto.JPG");
    
    imshow("input", img);

    draw_rectangle(img);

    

    waitKey(0);

}
