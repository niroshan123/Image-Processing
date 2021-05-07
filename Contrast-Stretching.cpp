#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


//Contrast-Stretching

//All the OpenCV classes and functions are placed into the cv namespace. 
using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

	//Get an Image argv[1]->Command line .exe, 1-> Colored Image
	Mat img = imread(argv[1], 1);


	//Check The Availability of the image
	if (!img.data) {
		cout << "File Not Found" << endl;
		return -1;
	}

	int height = img.rows;
	int width = img.cols;
	int widthStep = img.step;
	int ch = img.channels();

	//first check the image  whthere it is colored or gray in properties 24 nm its colored so to our practicals we wants to make it gray
	Mat gray(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//get a copy of the grey image
	Mat new_image = gray.clone();


	int v;

	int output;



	for (int y = 0; y < height; y++) {

		for (int x = 0; x < width; x++) {

			v = (int)gray.at<uchar>(y, x);

			if (v >= 0 && v <= 105) {

				output = int((5 / 105) * v);

			}

			else if (v > 105 && v <= 240) {

				output = int((245 / 135) * (v - 105) + 5);

			}

			else if (v > 240 && v <= 255) {

				output = int((5 / 15) * (v - 240) + 250);

			}

			new_image.at<uchar>(y, x) = (uchar)output;

		}

	}
	

	//Load the image and show in the window
	namedWindow("LoadOriginalImage");
	imshow("LoadOriginalImage", img);
	
	namedWindow("Gray_Converted");
	imshow("Gray_Converted", gray);
	namedWindow("Gray_Copy");
	imshow("Gray_Copy", new_image);

	
	waitKey(0);
	return 0;

}
