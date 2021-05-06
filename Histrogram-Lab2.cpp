#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


//All the OpenCV classes and functions are placed into the cv namespace. 
using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

	//Get an Image argv[1]->Command line .exe, 1-> Colored Image
	Mat img = imread(argv[1],1);


	//Check The Availability of the image
	if (!img.data) {
		cout << "File Not Found" << endl;
		return -1;
	}

	int height = img.rows;
	int width = img.cols;
	int widthStep = img.step;
	int ch = img.channels();


	//Pixel Reading in Mat Structure
	img.at<uchar>(10, 10) = 255; //access the (10,10) and make it white

	//Create an empty black window Scalar 0 --> Black image ,  CV_8UC1 --> Channel 1 8 bits
	Mat black(height, width, CV_8UC1, Scalar(0));

	//Create another window and load the original img by converting that into black and white
	Mat gray(height, width, CV_8UC1, Scalar(0));
	//converting img to gray image
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//create a copy of original image img
	Mat imgCopy(height, width, CV_8UC3, Scalar(0, 0, 0));
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			imgCopy.at<Vec3b>(y, x) = img.at<Vec3b>(y, x);
		}
	}
	

	//Designing the Histogram
	int hist[256];

	//Initialize “0” to all the array elements

	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	//Count one by one pixel for each intensity value
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			hist[(int)gray.at<uchar>(y, x)] = hist[(int)gray.at<uchar>(y, x)] + 1;
		}
	}

	//print the values of all intentisity levels
	for (int i = 0; i < 256; i++) {
		cout << i<<":" << hist[i] <<endl;
		
	}

	//draw the histogram

	int histImage_H = 400;
	int histImage_W = 510;
	int bin_w = cvRound((double)histImage_W / 256);

	Mat histImage(histImage_H,histImage_W,CV_8UC1, Scalar(255));

	//Find the maximum number of pixels from histogram array
	int max = hist[0];
	for (int i = 0; i < 256; i++) {
		if(max < hist[i])
		{
			max = hist[i];
		}
	}
	//Normalize the histogram between 0 and histogram height

	for (int i = 0; i < 256; i++) {
		//hist[i] = ((double)hist[i] / max) * histImage.rows ;
	
	}

	//Draw the lines of histogram

	
		
	

	for (int i = 0; i < 256; i++) {
		line(histImage, Point(bin_w*(i), histImage_H), Point(bin_w*(i), histImage_H - hist[i]),Scalar(0),1,8,0);

	}


	//Load the image and show in the window
	namedWindow("LoadOriginalImage");
	imshow("LoadOriginalImage", img);


	//Load the black image and show in the window
	namedWindow("BlackBackGround");
	imshow("BlackBackGround", black);

	//Load the gray image and show in the window
	namedWindow("Gray Image");
	imshow("Gray Image", gray);

	//Load the copy image and show in the window
	namedWindow("Copy Image");
	imshow("Copy Image", imgCopy);

	namedWindow("Hist_Image");
	imshow("Hist_Image", histImage);

	waitKey(0);
	return 0;
	
}
