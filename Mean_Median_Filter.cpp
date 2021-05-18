
#include "opencv2/opencv.hpp"

#include "opencv2/highgui.hpp"

#include "opencv2/core.hpp"



using namespace cv;

using namespace std;



void insertionSort(int arr[], int n)

{

	int i, key, j;

	for (i = 1; i < n; i++)

	{

		key = arr[i];

		j = i - 1;



		/* Move elements of arr[0..i-1], that are

		greater than key, to one position ahead

		of their current position */

		while (j >= 0 && arr[j] > key)

		{

			arr[j + 1] = arr[j];

			j = j - 1;

		}

		arr[j + 1] = key;

	}

}





int main(int argc, char* argv[]) {

	if (argc != 3) {

		printf("Enter exeFileName ImageName kernelSize");

		return -1;

	}



	Mat img = imread(argv[1], 1);



	if (!img.data) {

		cout << "Could not find the image!" << endl;

		return -1;

	}



	int height = img.rows;

	int width = img.cols;

	int widthstep = img.step;

	int ch = img.channels();





	Mat gray(height, width, CV_8UC1, Scalar(0));

	cvtColor(img, gray, COLOR_BGR2GRAY);



	Mat output = gray.clone();



	int k = atoi(argv[2]);

	int adj = k / 2;



	/*int sum;

	int avg = 0;

	for (int i = adj; i < height - adj; i++) {

		for (int j = adj; j < width - adj; j++) {

			sum = 0;

			for (int g = i - adj; g <= i + adj; g++) {

				for (int h = j - adj; h <= j + adj; h++) {

					sum = sum + (int)gray.at<uchar>(g, h);

				}

			}

			avg = sum / (k * k);

			output.at<uchar>(i, j) = (uchar)avg;

		}

	}*/



	int size = k * k;

	int* arr = new int[size];

	int index; 

	int middle;

	for (int i = adj; i < height - adj; i++) {

		for (int j = adj; j < width - adj; j++) {

			index = 0;

			for (int g = i - adj; g <= i + adj; g++) {

				for (int h = j - adj; h <= j + adj; h++) {

					arr[index]= (int)gray.at<uchar>(g, h);

					index++;

				}

			}

			insertionSort(arr, size);

			middle = size / 2;

			output.at<uchar>(i, j) = (uchar)arr[middle];

		}

	}

	namedWindow("Gray");

	imshow("Gray", gray);

	namedWindow("Output");

	imshow("Output", output);

	waitKey(0);

	return 0;

}
