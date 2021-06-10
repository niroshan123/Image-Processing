
#include "opencv2/opencv.hpp"

#include "opencv2/highgui.hpp"

#include "opencv2/core.hpp"



using namespace cv;

using namespace std;



int main(int argc, char* argv[]) {

	Mat img = imread(argv[1], 1);



	if (!img.data) {

		cout << "Could not find the image!" << endl;

		return -1;

	}

	int height = img.rows;
	int width = img.cols;
	int widthstep = img.step;

	int ch = img.channels();

	
	

	Mat grayImage(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, grayImage, COLOR_BGR2GRAY);

	//get a copy of the grey image
	Mat output = grayImage.clone();

	//creating varible for x direction gradient 

	int gx = 0;


	//creating varible for y direction gradient 

	int gy = 0;

	//creating varible for overall gradient 

	int G = 0;

	//to get the Threshold from the cmd itself

	int T = atoi(argv[2]);

	for (int i = 0; i < height - 1; i++) {
		for (int j = 0; j < width - 1; j++) {
			gx = grayImage.at<uchar>(i, j) - grayImage.at<uchar>(i, j + 1);
			gy = grayImage.at<uchar>(i + 1, j) - grayImage.at<uchar>(i + 1, j + 1);
			//getting the absolute value

			G = abs(gx) + abs(gy);

			if (G >= T) {
				output.at<uchar>(i, j) = 255;
			
			}
			else {
				output.at<uchar>(i, j) = 0;
			}



		}

	}


	namedWindow("Original_Image");

	imshow("Original_Image", img);

	namedWindow("Gray_Image");

	imshow("Gray_Image", grayImage);

	namedWindow("Edge_Detected_Image");

	imshow("Edge_Detected_Image", output);

	



	

	waitKey(0);

	return 0;

}
