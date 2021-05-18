
#include "opencv2/opencv.hpp"

#include "opencv2/highgui.hpp"

#include "opencv2/core.hpp"



using namespace cv;

using namespace std;



int main(int argc, char* argv[]) {

	Mat img = imread(argv[1], IMREAD_GRAYSCALE);



	if (!img.data) {

		cout << "Could not find the image!" << endl;

		return -1;

	}



	Mat copy = img.clone();



	//allocate memory location 

	int histogram[256];

	int equalhistogram[256];

	int cNew[256];

	double prob[256];

	double cprob[256];



	//initialized to 0

	for (int x=0; x < 256; x++) {

		histogram[x] = 0;

		equalhistogram[x] = 0;

		cNew[x] = 0;

		prob[x] = 0.0;

		cprob[x] = 0.0;

	}



	//calculate no of pixels for each gray level of original image

	for (int i = 0; i < img.rows; i++) {

		for (int j = 0; j < img.cols; j++) {

			histogram[(int)img.at<uchar>(i, j)] = histogram[(int)img.at<uchar>(i, j)] + 1;

		}

	}



	//total no of pixels

	int N = img.rows * img.cols;

	

	//Calculate the probability of each gray level

	for (int i=0; i < 256; i++) {

		prob[i] = (double)histogram[i] / N;

	}



	//Generate cumulative probability

	cprob[0] = prob[0];

	for (int i=1; i < 256; i++) {

		cprob[i] = cprob[i - 1] + prob[i];

	}



	for (int i = 0; i < 256; i++) {

		printf("%f\n", cprob[i]);

	}



	//Scale cumulative probability

	for (int i = 0; i < 256; i++) {

		cNew[i] = cvRound(cprob[i] * 255);

	}



	int z = 0;

	for (int i = 0; i < img.rows; i++) {

		for (int j = 0; j < img.cols; j++) {

			z = cNew[(int)img.at<uchar>(i, j)];

			copy.at<uchar>(i,j) = (uchar)z;

		}

	}



	//calculate no of pixels for each gray level of equalized image

	for (int i = 0; i < copy.rows; i++) {

		for (int j = 0; j < copy.cols; j++) {

			equalhistogram[(int)copy.at<uchar>(i, j)] = equalhistogram[(int)copy.at<uchar>(i, j)] + 1;

		}

	}



	//draw histograms

	int hist_w = 512;

	int hist_h = 400;



	Mat equalHistImg(hist_h, hist_w, CV_8UC1, Scalar(255));

	Mat oriHistImg(hist_h, hist_w, CV_8UC1, Scalar(255));



	// find the maximum intensity element from histogram

	int max = equalhistogram[0];

	for (int i = 1; i < 256; i++) {

		if (max < equalhistogram[i]) {

			max = equalhistogram[i];

		}

	}



	int omax = histogram[0];

	for (int i = 1; i < 256; i++) {

		if (omax < histogram[i]) {

			omax = histogram[i];

		}

	}



	// normalize the histograms

	for (int i = 0; i < 256; i++) {

		equalhistogram[i] = ((double)equalhistogram[i] / max) * equalHistImg.rows;

	}



	for (int i = 0; i < 256; i++) {

		histogram[i] = ((double)histogram[i] / omax) * img.rows;

	}



	int bin_w = cvRound((double)hist_w / 256);



	// draw the intensity line for histogram

	for (int i = 0; i < 256; i++)

	{

		line(equalHistImg, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - equalhistogram[i]), Scalar(0), 1, 8, 0);

	}



	for (int i = 0; i < 256; i++)

	{

		line(oriHistImg, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - histogram[i]), Scalar(0), 1, 8, 0);

	}



	namedWindow("Image");

	imshow("Image", img);

	namedWindow("Equalized Image");

	imshow("Equalized Image", copy);

	namedWindow("Equalized Image Histogram");

	imshow("Equalized Image Histogram", equalHistImg);

	namedWindow("Original Image Histogram");

	imshow("Original Image Histogram", oriHistImg);

	waitKey(0);

	return 0;

}
