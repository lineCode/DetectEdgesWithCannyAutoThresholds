#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
int num_pixels_img = 0;
RNG rng(12345);

/// Function header
Mat auto_canny(Mat, float = 0.33 );

/* @function main */
int main(int argc, char** argv)
{
	/// Load source image and convert it to gray
	src = imread(argv[1], 1);
	num_pixels_img = src.rows * src.cols;
	/// Convert image to gray and blur it
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	/// Create Window
	char* source_window = "Source";
	namedWindow(source_window, WINDOW_AUTOSIZE);
	imshow(source_window, src);

	Mat canny_output = auto_canny(src_gray);

	/// Show in a window
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", canny_output);

	waitKey(0);
	return(0);
}

Mat auto_canny(Mat image, float sigma)
{
	Mat a;
	Scalar average = mean(image);
	double median = average[0];
	//apply automatic Canny edge detection using the computed median
	int lower = (1.0 - sigma) * median;
	if (lower < 0) lower = 0;
	int upper = (1.0 + sigma) * median;
	if (upper > 255) upper = 255;
	Mat edge;
	Canny(image, edge, lower, upper);
	return edge;
}
