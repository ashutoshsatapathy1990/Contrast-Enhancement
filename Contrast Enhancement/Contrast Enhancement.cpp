/* -------------------------------------------------------------------------------------------------|
IMAGE CONTRAST ENHANCEMENT IN SPATIAL DOMAIN USING LINEAR, PIECEWISE LINEAR, EXP., LOG. STRETCHING. |
IMAGE CONTRAST ENHANCEMENT IN SPATIAL DOMAIN USING POWER LAW TRANSFORMATION.						|
IMAGE CONTRAST ENHANCEMENT IN SPATIAL DOMAIN USING HE, CONTRAST LIMITED HISTOGRAM EQUALIZATION.		|
IMAGE CONTRAST ENHANCEMENT IN SPATIAL DOMAIN USING BBHE, DSIHE AND CLADHE TECHNIQUES.				|
Contrast Enhancement.cpp : Defines the entry point for the console application.						|
...................................................................................................*/

/*...................................... HEADER FILES .............................................*/
// Include Necessary Header Files 
// [both in Std and Non Std Path]
#include "stdafx.h"
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<opencv\cv.h>
#include<opencv\highgui.h>
using namespace std;
using namespace cv;
/*........................................... END .................................................*/

/*.................................... LINEAR STRETCHING ..........................................*/
// Contrast enhancement of [R, G, B] channels individually using linear stretching method. 
void Linear_Stretch(Mat* Image, double* min, double* max, int row, int col)
{
		for (int j = 0; j < row * col; j++)
		{
			float R = Image[0].at<uchar>(j/row, j%row) - min[0];
			float G = Image[1].at<uchar>(j/row, j%row) - min[1];
			float B = Image[2].at<uchar>(j/row, j%row) - min[2];
			Image[0].data[j] = R * 255 / (max[0] - min[0]);
			Image[1].data[j] = G * 255 / (max[1] - min[1]);
			Image[2].data[j] = B * 255 / (max[2] - min[2]);
		}
}
/*........................................... END .................................................*/

/*.................................... LOGARITHIMIC STRETCHING ..........................................*/
// Contrast enhancement of [R, G, B] channels individually using logarithimic stretching method. 
void Log_Stretch(Mat* Image, int row, int col)
{
	for (int j = 0; j < row * col; j++)
	{
		Image[0].data[j] = 64 * log2(Image[0].at<uchar>(j / row, j%row) + 1);
		Image[1].data[j] = 64 * log2(Image[1].at<uchar>(j / row, j%row) + 1);
		Image[2].data[j] = 64 * log2(Image[2].at<uchar>(j / row, j%row) + 1);
	}
}
/*........................................... END .................................................*/

/*...................................... MAIN PROGRAM .............................................*/
int main()
{
	// Create Variables to Store Actual Values of [R, G, B] Cheannels.
	// 'Select' Variable for selection of The Enhancement Method.  
	// Arrays to store min and max intensities of each channels [R, G, B].
	Mat RGB_Image[3]; int Select; double min[3], max[3];

	printf("Selection of The Enhancement Methods:\n [1]Linear\n [2]Piece-Wise Linear\n [3]Logarithimic\n");
	printf("[4]Exponential\n [5]Power-Law\n [6]Histogram Equalization\n [7] Adaptive Histogram Equalization\n");
	printf("[8]Brightness Preserving Bi-Histogram Eq.\n [9]Dualistic Subimage Histogram Eq.\n [10]CLAHE\n");
	scanf("%d", &Select);

	// Read Image Data from Image File
	Mat Image = imread("img1.bmp", CV_LOAD_IMAGE_COLOR);

	// Check, Whether Program Open Image File
	if (!Image.data)
	{
		printf("COULDN'T OPEN OR READ IMAGE FILE");
		return -1;
	}

	// Display The Input Image
	namedWindow("ORIGINAL IMAGE", WINDOW_NORMAL);
	imshow("ORIGINAL IMAGE", Image);

	// Convert Each Channel Pixel Values from 8U to 32F
	// Copy Image.data values to RGB_Image for Extracting All Three Frames [R, G, B] 
	Image.convertTo(Image, CV_32F);
	split(Image, RGB_Image);

	// Store minimum and maximum values of [R, G, B] channels separately.
	for (int i = 0; i < 3; i++)
	{
		minMaxLoc(RGB_Image[i], &min[i], &max[i]);
		RGB_Image[i].convertTo(RGB_Image[i], CV_8U);
	}

	// Selection of The Enhancement Method
	switch (Select)
	{
	case 1: printf("You Selected Linear Stretching \n");
		Linear_Stretch(RGB_Image, min, max, Image.rows, Image.cols);
		break;
	case 2: printf("You Selected Piece-Wise Linear Stretching \n");
		//LP_Gaussian_Filter(LPFilter, CUTOFF);
		break;
	case 3:	printf("You Selected Logarithimic Stretching \n");
		Log_Stretch(RGB_Image, Image.rows, Image.cols);
		break;
	case 4:	printf("You Selected Exponential Stretching \n");
		//LP_Butterworth_Filter(LPFilter, CUTOFF, ord);
		break;
	case 5:	printf("You Selected Power-Law Transformation \n");
		//LP_Butterworth_Filter(LPFilter, CUTOFF, ord);
		break;
	case 6:	printf("You Selected Histogram Equalizationn \n");
		//LP_Butterworth_Filter(LPFilter, CUTOFF, ord);
		break;
	case 7:	printf("You Selected Adaptive histogram Equalization \n");
		//LP_Butterworth_Filter(LPFilter, CUTOFF, ord);
		break;
	case 8:	printf("You Selected BBHE \n");
		//LP_Butterworth_Filter(LPFilter, CUTOFF, ord);
		break;
	case 9:	printf("You Selected DSIHE \n");
		//LP_Butterworth_Filter(LPFilter, CUTOFF, ord);
		break;
	case 10: printf("You Selected CLAHE \n");
		//LP_Butterworth_Filter(LPFilter, CUTOFF, ord);
		break;
	default: printf("Wrong Selection \n");
		break;
	}

	merge(RGB_Image, 3, Image);
	Image.convertTo(Image, CV_8U);

	// Display Final Enhanced Image 
	namedWindow("ENHANCED IMAGE", WINDOW_NORMAL);
	imshow("ENHANCED IMAGE", Image);

	waitKey(0);
    return 0;
}
/*........................................... END .................................................*/

