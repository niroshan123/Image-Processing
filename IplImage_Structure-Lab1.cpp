#include "cv.h"
#include "highgui.h"

int main(int argc, char* argv[]) {

	IplImage* img; //Declare a new IplImage pointer

	img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR); //Load image using cvLoadImage() 

	//and Check image exist or not

	if (!img) {
		printf("The image file %s is not exists", argv[1]);
		return -1;
	}


	//2. Print height, width, width step and number of channels of the image using IplImage pointer
	
	int width = img->width;
	int height = img->height;
	int widthS = img->widthStep;
	int channels = img->nChannels;

	IplImage* white100 = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);


	printf("Image Width : %d \n", width);
	printf("Image Height : %d \n", height);
	printf("Image WidthStep : %d \n", widthS);
	printf("Image Num of Channels : %d \n", channels);

	// Make the 100,100 pixel black
	int i = 100;
	int j = 100;

	uchar* data = (uchar*)img->imageData; // get the values of image

	int b = data[i*widthS + j*channels];//assign the channel 1(blue) value to an integer
	int g = data[i*widthS + j * channels+1];//assign the channel 2(green) value to an integer
	int r = data[i*widthS + j * channels+2];//assign the channel 3(red) value to an integer

	printf("Blue Value : %d \n", b);
	printf("Green Value : %d \n", g);
	printf("Red Value : %d \n", r);

	data[i*widthS + j * channels] = 255;
	data[i*widthS + j * channels+1] = 255;
	data[i*widthS + j * channels+2] = 255;

	for (int p = 0; p < 100; p++) {
		for (int q = 0; q < 100; q++) {

			data[p*widthS + q * channels] = 255;
			data[p*widthS + q * channels + 1] = 255;
			data[p*widthS + q * channels + 2] = 255;

			
		}
	}

	uchar* data100 = (uchar*)white100->imageData;

	for (int p = 0; p < height; p++) {
		for (int q = 0; q < width; q++) {

			data100[p*widthS + q * channels] = data[p*widthS + q * channels];
			data100[p*widthS + q * channels + 1] = data[p*widthS + q * channels+1];
			data100[p*widthS + q * channels + 2] = data[p*widthS + q * channels+2];


		}
	}

	for (int p = 0; p < 100; p++) {
		for (int q = 0; q < 100; q++) {

			data100[p*widthS + q * channels] = 0;
			data100[p*widthS + q * channels + 1] = 0;
			data100[p*widthS + q * channels + 2] = 0;


		}
	}

	IplImage* blankImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	uchar* blankData = (uchar*)blankImg->imageData;
	int blankWS = blankImg->widthStep;
	int blankChannels = blankImg->nChannels;


	for (int p = 0; p < height; p++) {
		for (int q = 0; q < width; q++) {

			blankData[p*blankWS + q * blankChannels] = 0;
			
		}
	}


	//6. Convert BGR image to grayscale image.

	IplImage* BGR2Gray = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	uchar* BGR2GrayData = (uchar*)BGR2Gray->imageData;
	int BGR2GrayWS = blankImg->widthStep;
	int BGR2GrayChannels = blankImg->nChannels;

	for (int p = 0; p < height; p++) {
		for (int q = 0; q < width; q++) {

			BGR2GrayData[p*BGR2GrayWS + q * BGR2GrayChannels] = data[p*widthS + q * channels]*0.1140 +
				data[p*widthS + q * channels+1]*0.5870 + data[p*widthS + q * channels+2]*0.2989;

		}
	}

	IplImage* Binary = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	uchar* BinaryData = (uchar*)Binary->imageData;

	for (int p = 0; p < height; p++) {
		for (int q = 0; q < width; q++) {

			if (BGR2GrayData[p*BGR2GrayWS + q * BGR2GrayChannels] > 160) {
				BinaryData[p*BGR2GrayWS + q * BGR2GrayChannels] = 255;
			}
			else {
				BinaryData[p*BGR2GrayWS + q * BGR2GrayChannels] = 0;

			}

		}

	}

	IplImage* InvertBGR = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	uchar* InvertBGRData = (uchar*)InvertBGR->imageData;
	int InvertBGRWS = InvertBGR->widthStep;
	int InvertBGRChannels = InvertBGR->nChannels;

	for (int p = 0; p < height; p++) {
		for (int q = 0; q < width; q++) {

			InvertBGRData[p*InvertBGRWS + q * InvertBGRChannels] = 255-data[p*widthS + q * channels];
			InvertBGRData[p*InvertBGRWS + q * InvertBGRChannels + 1] = 255- data[p*widthS + q * channels + 1];
			InvertBGRData[p*InvertBGRWS + q * InvertBGRChannels + 2] = 255-data[p*widthS + q * channels + 2];
			
			
		}

	}

	IplImage* blue = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	uchar* blueData = (uchar*)blue->imageData;

	IplImage* green = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	uchar* greenData = (uchar*)green->imageData;

	IplImage* red = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	uchar* redData = (uchar*)red->imageData;


	for (int p = 0; p < height; p++) {
		for (int q = 0; q < width; q++) {

			blueData[p*widthS + q * channels] = data[p*widthS + q * channels];
			blueData[p*widthS + q * channels + 1] = 0;
			blueData[p*widthS + q * channels + 2] = 0;

			greenData[p*widthS + q * channels] = 0;
			greenData[p*widthS + q * channels + 1] = data[p*widthS + q * channels+1];
			greenData[p*widthS + q * channels + 2] = 0;

			redData[p*widthS + q * channels] = 0;
			redData[p*widthS + q * channels + 1] = 0;
			redData[p*widthS + q * channels + 2] = data[p*widthS + q * channels+2];


		}

	}



	//Display image window using cvNamedWindow() and cvShowImage()
	cvNamedWindow("Image");
	cvShowImage("Image", img);

	cvNamedWindow("Image100");
	cvShowImage("Image100", white100);

	cvNamedWindow("BlankImage");
	cvShowImage("BlankImage", blankImg);

	cvNamedWindow("BGR2Gray");
	cvShowImage("BGR2Gray", BGR2Gray);

	cvNamedWindow("Binary");
	cvShowImage("Binary", Binary);

	cvNamedWindow("InvertBGR");
	cvShowImage("InvertBGR", InvertBGR);

	cvNamedWindow("Blue");
	cvShowImage("Blue", blue);

	cvNamedWindow("Green");
	cvShowImage("Green", green);

	cvNamedWindow("Red");
	cvShowImage("Red", red);

	cvWaitKey(0); //Wait image window until a keyboard button press using cvWaitKey()

	cvDestroyWindow("Image"); //Destroy image window using cvDestroyWindow()
	cvDestroyWindow("Image100");
	cvDestroyWindow("BlankImage");
	cvDestroyWindow("BGR2Gray");
	cvDestroyWindow("Binary");
	cvDestroyWindow("InvertBGR");
	cvDestroyWindow("Blue");
	cvDestroyWindow("Green");
	cvDestroyWindow("Red");

	cvReleaseImage(&img); //Release image using cvReleaseImage()
	cvReleaseImage(&white100);
	cvReleaseImage(&blankImg);
	cvReleaseImage(&BGR2Gray);
	cvReleaseImage(&Binary);
	cvReleaseImage(&InvertBGR);
	cvReleaseImage(&blue);
	cvReleaseImage(&green);
	cvReleaseImage(&red);

	return 0;

	

}
