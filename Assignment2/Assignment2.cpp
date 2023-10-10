#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace cv;

float Box_Muller() {

	float X, Y;
	X = (rand() % 10000) / 10000.0;
	Y = (rand() % 10000) / 10000.0;

	return sqrt(-2 * log(X)) * cos(2 * 3.14159 * Y);
}

// 画像にノイズを加える
void add_noise(Mat& img, Mat & out, float sigma) {
	// ガウスノイズを加える
        img.copyTo(out);
	for (int ptr = 0; ptr < 3 * img.cols * img.rows; ptr++) {
		int v = img.data[ptr] + Box_Muller() * sigma;
		if (v < 0)v = 0;
		if (v > 255)v = 255;
		out.data[ptr] = v;
	}
}

void meanfilter2D(Mat& in, Mat& out, Mat& f){

    int w, h, fw, fh;
    w = in.cols; h = in.rows;
    fw = f.cols; fh = f.rows;

    if (fw != fh || fw % 2 == 0) return;

    int N = (fw - 1) / 2;
    out = Mat(h, w, CV_8UC3);

    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){

            Vec3f p = 0;

            for (int sy = -N; sy <= N; sy++){
                int ty = y + sy;
                if (ty < 0) ty = -ty; else if (ty >= h) ty = h - 1 - (h - sy);
                for (int sx = -N; sx <= N; sx++){
                    int tx = x + sx;
                    if (tx < 0) tx = -tx; else if (tx >= w) tx = w - 1 - (sx - w);
                    p = p + (Vec3f)in.at<Vec3b>(ty, tx) * f.at<double>(sy + N, sx + N);
                }
            }

            out.at<Vec3b>(y, x) = p;
        }
    }

}

void gaussianfilter(Mat& in, Mat& g_out, Mat& f){

    int w, h, fw, fh;
    w = in.cols; h = in.rows;
    fw = f.cols; fh = f.rows;

    if ( fw != fh || fw % 2 == 0) return;

    int N = (fw - 1) / 2;
    g_out = Mat(h, w, CV_8UC3);

    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){

            Vec3f p = 0;

            for (int sy = -N; sy <= N; sy++){
                int ty = y + sy;
                if (ty < 0) ty = -ty; else if (ty >= h) ty = h - 1 - (h - sy);
                for (int sx = -N; sx <= N; sx++){
                    int tx = x + sx;
                    if (tx < 0) tx = -tx; else if (tx >= w) tx = w - 1 - (sx - w);
                    p = p + (Vec3f)in.at<Vec3b>(ty, tx) * f.at<double>(sy + N, sx + N);
                }
            }
            g_out.at<Vec3b>(y, x) = p;
        }
    }
}

double calculatePSNR(Mat& in, Mat& a_out){

    int w = in.cols; 
    int h = in.rows;
    double max = 255.0;
    double mse = 0;
    double psnr = 0, mseR = 0.0, mseG = 0.0, mseB = 0.0;

    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){

            Vec3b in_pixel = in.at<Vec3b>(y, x);
            Vec3b out_pixel = a_out.at<Vec3b>(y, x);

            mseR += pow(static_cast<double>(in_pixel[2] - out_pixel[2]), 2);
            mseG += pow(static_cast<double>(in_pixel[1] - out_pixel[1]), 2);
            mseB += pow(static_cast<double>(in_pixel[0] - out_pixel[0]), 2);
            
        }
    }
    
    mseR /= static_cast<double>(h * w);
    mseG /= static_cast<double>(h * w);
    mseB /= static_cast<double>(h * w);
    mse = (mseR + mseG + mseB) / 3.0;
    psnr = 10.0 * log10(pow(max, 2) / mse);

    return psnr;
}
int main(){

    Mat img = imread("/Users/renchinsuren/Documents/2023B/Computer Vision/Assigment1/myphoto.JPG");

    resize(img, img, Size(800, 800 * img.rows / img.cols));
    float noise = 30.0;
    Mat noise_out;
    add_noise(img, noise_out, noise);
    //imwrite("ass2Nois.jpg", noise_out);

    std::vector<int> kernel = {3, 5, 7, 9, 11, 13, 15};
    std::vector<double> mean_psnr_values, g_psnr_values;

    for (int h_size : kernel){
        Mat h(h_size, h_size, CV_64F);
        h = 1.0 / (h_size * h_size);

        Mat out;
        meanfilter2D(noise_out, out, h);
        //std::string output_filename = "ass2Mean" + std::to_string(h_size) + ".jpg";
        //imwrite(output_filename, out);

        double mean_psnr = calculatePSNR(img, out);
        mean_psnr_values.push_back(mean_psnr);

        // *************** GaussianFilter ***************
        float sigma = h_size / 6.0;
        Mat g_h(h_size, h_size, CV_64F);
        double sum = 0;

        for (int sy = 0; sy < h_size; sy++){
            for (int sx = 0; sx < h_size; sx++){
                int x = sx - (h_size - 1) / 2;
                int y = sy - (h_size - 1) / 2;
                double g = exp(-(x * x + y * y) / (2.0 * sigma * sigma)) / (2 * 3.14159 * sigma * sigma);
                g_h.at<double>(sy, sx) = g;
                sum += g;
            }
        }

        g_h = g_h * (1 / sum);

        Mat g_out;
        gaussianfilter(noise_out, g_out, g_h);
        //std::string outpu = "ass2Gaus" + std::to_string(h_size) + ".jpg";
        //imwrite(outpu, g_out);

        double g_psnr = calculatePSNR(img, g_out);
        g_psnr_values.push_back(g_psnr);

    }
    
    
    
    std::ofstream data_file("psnr_data.txt");

    if (!data_file.is_open()) {
        std::cerr << "Error: Unable to create data file." << std::endl;
        return 1;
    }

    for (size_t i = 0; i < kernel.size(); i++) {
        data_file << kernel[i] << " " << mean_psnr_values[i] << " " << g_psnr_values[i] << std::endl;
    }

    data_file.close();

    std::ofstream gnuplot_script("gnuplot_script.plt");
    gnuplot_script << "set terminal pngcairo enhanced size 800,600\n";
    gnuplot_script << "set output 'psnr_plot.png'\n";
    gnuplot_script << "set xlabel 'Kernel size'\n";
    gnuplot_script << "set ylabel 'PSNR'\n";
    gnuplot_script << "set title 'PSNR vs. Kernel Size'\n";
    gnuplot_script << "plot 'psnr_data.txt' using 1:2 with linespoints title 'Mean Filter', '' using 1:3 with linespoints title 'Gaussian Filter'\n";
    gnuplot_script.close();

    std::string gnuplot_command = "gnuplot gnuplot_script.plt";
    int gnuplot_result = system(gnuplot_command.c_str());

    if (gnuplot_result != 0) {
        std::cerr << "Error: Gnuplot command execution failed." << std::endl;
        return 1;
    }

    return 0;
}