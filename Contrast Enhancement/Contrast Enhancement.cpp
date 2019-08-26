/* -------------------------------------------------------------------------------------------------|
IMAGE CONTRAST ENHANCEMENT IN SPATIAL DOMAIN USING LINEAR, PIECEWISE LINEAR, EXP., LOG. STRETCHING. |
IMAGE CONTRAST ENHANCEMENT IN SPATIAL DOMAIN USING POWER LAW TRANSFORMATION.			    |
IMAGE CONTRAST ENHANCEMENT IN SPATIAL DOMAIN USING HE, CONTRAST LIMITED HISTOGRAM EQUALIZATION.	    |
IMAGE CONTRAST ENHANCEMENT IN SPATIAL DOMAIN USING BBHE, DSIHE AND CLADHE TECHNIQUES.		    |
Contrast Enhancement.cpp : Defines the entry point for the console application.			    |
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

/*............................... PIECEWISE LINEAR STRETCHING ......................................*/
// Contrast enhancement of [R, G, B] channels individually using piecewise linear stretching method. 
void PW_Linear_Stretch(Mat* Image, double* min, double* max, int row, int col, int Seg)
{
	float Rrange = max[0] - min[0] + 1;
	float Grange = max[1] - min[1] + 1;
	float Brange = max[2] - min[2] + 1;
	float Rfinal, Gfinal, Bfinal;
	for (int j = 0; j < row * col; j++){
	float R = Image[0].at<uchar>(j / row, j%row);
	float G = Image[1].at<uchar>(j / row, j%row);
	float B = Image[2].at<uchar>(j / row, j%row);
	if (Seg == 3) {
		float Rfold = Rrange / 3;
		float Gfold = Grange / 3;
		float Bfold = Brange / 3;
		if (R >= min[0] && R <= min[0] + Rfold - 1){
		Rfinal = 63 / (Rfold - 1) * (R - min[0]);}
		else if (R > min[0] + Rfold - 1 && R <= min[0] + 2 * Rfold - 1){
		Rfinal = 128 / (Rfold) * (R - min[0] - Rfold + 1) + 63;}
		else{Rfinal = 64 / (Rfold) * (R - min[0] - 2 * Rfold + 1) + 191;}
		if (G >= min[0] && G <= min[0] + Gfold - 1){
		Gfinal = 63 / (Gfold - 1) * (G - min[0]);}
		else if (G > min[0] + Gfold - 1 && G <= min[0] + 2 * Gfold - 1){
		Gfinal = 128 / (Gfold) * (G - min[0] - Gfold + 1) + 63;}
		else{Gfinal = 64 / (Gfold) * (G - min[0] - 2 * Gfold + 1) + 191;}
		if (B >= min[0] && B <= min[0] + Bfold - 1){
		Bfinal = 63 / (Bfold - 1) * (B - min[0]);}
		else if (B > min[0] + Bfold - 1 && B <= min[0] + 2 * Bfold - 1){
		Bfinal = 128 / (Bfold) * (B - min[0] - Bfold + 1) + 63;}
		else{Bfinal = 64 / (Bfold) * (B - min[0] - 2 * Bfold + 1) + 191;} }
	else if (Seg == 4)
	{
		float Rfold = Rrange / 4;
		float Gfold = Grange / 4;
		float Bfold = Brange / 4;
		if (R >= min[0] && R <= min[0] + Rfold - 1) {
		Rfinal = 31 / (Rfold - 1) * (R - min[0]);}
		else if (R > min[0] + Rfold - 1 && R <= min[0] + 2 * Rfold - 1) {
		Rfinal = 96 / (Rfold) * (R - min[0] - Rfold + 1) + 31;}
		else if (R > min[0] + 2 * Rfold - 1 && R <= min[0] + 3 * Rfold - 1) {
		Rfinal = 96 / (Rfold) * (R - min[0] - 2 * Rfold + 1) + 127;}
		else {Rfinal = 32 / (Rfold) * (R - min[0] - 3 * Rfold + 1) + 191;}
		if (G >= min[0] && G <= min[0] + Gfold - 1) {
		Gfinal = 31 / (Gfold - 1) * (G - min[0]);}
		else if (G > min[0] + Gfold - 1 && G <= min[0] + 2 * Gfold - 1) {
		Gfinal = 96 / (Gfold) * (G - min[0] - Gfold + 1) + 31;}
		else if (G > min[0] + 2 * Gfold - 1 && G <= min[0] + 3 * Gfold - 1) {
		Gfinal = 96 / (Gfold) * (G - min[0] - 2 * Gfold + 1) + 127;}
		else {Gfinal = 32 / (Gfold) * (G - min[0] - 3 * Gfold + 1) + 191;}
		if (B >= min[0] && B <= min[0] + Bfold - 1) {
		Bfinal = 31 / (Bfold - 1) * (B - min[0]);}
		else if (B > min[0] + Bfold - 1 && B <= min[0] + 2 * Bfold - 1) {
		Bfinal = 96 / (Bfold) * (B - min[0] - Bfold + 1) + 31;}
		else if (B > min[0] + 2 * Bfold - 1 && B <= min[0] + 3 * Bfold - 1) {
		Bfinal = 96 / (Bfold) * (B - min[0] - 2 * Bfold + 1) + 127;}
		else {Bfinal = 32 / (Bfold) * (B - min[0] - 3 * Bfold + 1) + 191;} }
	else
	{
		float Rfold = Rrange / 5;
		float Gfold = Grange / 5;
		float Bfold = Brange / 5;
		if (R >= min[0] && R <= min[0] + Rfold - 1) {
		Rfinal = 15 / (Rfold - 1) * (R - min[0]);}
		else if (R > min[0] + Rfold - 1 && R <= min[0] + 2 * Rfold - 1) {
		Rfinal = 64 / (Rfold) * (R - min[0] - Rfold + 1) + 15;}
		else if (R > min[0] + 2 * Rfold - 1 && R <= min[0] + 3 * Rfold - 1) {
		Rfinal = 96 / (Rfold) * (R - min[0] - 2 * Rfold + 1) + 79;}
		else if (R > min[0] + 3 * Rfold - 1 && R <= min[0] + 4 * Rfold - 1) {
		Rfinal = 64 / (Rfold) * (R - min[0] - 3 * Rfold + 1) + 175;}
		else {Rfinal = 16 / (Rfold) * (R - min[0] - 4 * Rfold + 1) + 239;}
		if (G >= min[0] && G <= min[0] + Gfold - 1) {
		Gfinal = 15 / (Gfold - 1) * (G - min[0]);}
		else if (G > min[0] + Gfold - 1 && G <= min[0] + 2 * Gfold - 1) {
		Gfinal = 64 / (Gfold) * (G - min[0] - Gfold + 1) + 15;}
		else if (G > min[0] + 2 * Gfold - 1 && G <= min[0] + 3 * Gfold - 1) {
		Gfinal = 96 / (Gfold) * (G - min[0] - 2 * Gfold + 1) + 79;}
		else if (G > min[0] + 3 * Gfold - 1 && G <= min[0] + 4 * Gfold - 1) {
		Gfinal = 64 / (Gfold) * (G - min[0] - 3 * Gfold + 1) + 175;}
		else {Gfinal = 16 / (Gfold) * (G - min[0] - 4 * Gfold + 1) + 239;}
		if (B >= min[0] && B <= min[0] + Bfold - 1) {
		Bfinal = 15 / (Bfold - 1) * (B - min[0]);}
		else if (B > min[0] + Bfold - 1 && B <= min[0] + 2 * Bfold - 1) {
		Bfinal = 64 / (Bfold) * (B - min[0] - Bfold + 1) + 15;}
		else if (B > min[0] + 2 * Bfold - 1 && B <= min[0] + 3 * Bfold - 1) {
		Bfinal = 96 / (Bfold) * (B - min[0] - 2 * Bfold + 1) + 79;}
		else if (B > min[0] + 3 * Bfold - 1 && B <= min[0] + 4 * Bfold - 1) {
		Bfinal = 64 / (Bfold) * (B - min[0] - 3 * Bfold + 1) + 175;}
		else {Bfinal = 16 / (Bfold) * (B - min[0] - 4 * Bfold + 1) + 239;}
	}
	Image[0].data[j] = Rfinal;
	Image[1].data[j] = Gfinal;
	Image[2].data[j] = Bfinal;
	}
}
/*........................................... END .................................................*/

/*................................. LOGARITHIMIC STRETCHING .......................................*/
// Contrast enhancement of [R, G, B] channels individually using logarithimic stretching method. 
void Log_Stretch(Mat* Image, int row, int col)
{
	for (int j = 0; j < row * col; j++)
	{
		Image[0].data[j] = 46 * log(Image[0].at<uchar>(j / row, j % row) + 1);
		Image[1].data[j] = 46 * log(Image[1].at<uchar>(j / row, j % row) + 1);
		Image[2].data[j] = 46 * log(Image[2].at<uchar>(j / row, j % row) + 1);
	}
}
/*........................................... END .................................................*/

/*.................................. EXPONETIAL STRETCHING ........................................*/
// Contrast enhancement of [R, G, B] channels individually using exponential stretching method. 
void Exp_Stretch(Mat* Image, int row, int col)
{
	for (int j = 0; j < row * col; j++)
	{
		Image[0].data[j] = exp(0.02173 * (Image[0].at<uchar>(j / row, j % row)));
		Image[1].data[j] = exp(0.02173 * (Image[1].at<uchar>(j / row, j % row)));
		Image[2].data[j] = exp(0.02173 * (Image[2].at<uchar>(j / row, j % row)));
	}
}
/*........................................... END .................................................*/

/*............................... POWER LAW TRANSFORMATION ........................................*/
// Contrast enhancement of [R, G, B] channels individually using powerlaw transformation method. 
void Powlaw_Trans(Mat* Image, int row, int col, float power, float Const)
{
	for (int j = 0; j < row * col; j++)
	{
		Image[0].data[j] = Const*pow(Image[0].at<uchar>(j / row, j % row), power);
		Image[1].data[j] = Const*pow(Image[1].at<uchar>(j / row, j % row), power);
		Image[2].data[j] = Const*pow(Image[2].at<uchar>(j / row, j % row), power);
	}
}
/*........................................... END .................................................*/

/*................................. HISTOGRAM EQUALIZATION ........................................*/
// Contrast enhancement of [R, G, B] channels individually using global histogram equalization method. 
void Histogram_Equalization(Mat* Image)
{
	equalizeHist(Image[0], Image[0]);
	equalizeHist(Image[1], Image[1]);
	equalizeHist(Image[2], Image[2]);
}
/*........................................... END .................................................*/

/*............................ ADAPTIVE HISTOGRAM EQUALIZATION ....................................*/
// Contrast enhancement of [R, G, B] channels individually using adaptive histogram equalization method. 
void Adaptive_HE(Mat* Image)
{
	Ptr<CLAHE> clahe = createCLAHE();
	clahe->apply(Image[0], Image[0]);
	clahe->apply(Image[1], Image[1]);
	clahe->apply(Image[2], Image[2]);
}
/*........................................... END .................................................*/

/*.......................................... CLAHE ................................................*/
// Contrast enhancement of [R, G, B] channels individually using Contrast limited histogram equalization method. 
void CLAH_Equalization(Mat* Image, int limit)
{
	Ptr<CLAHE> clahe = createCLAHE();
	clahe->setClipLimit(limit);
	clahe->apply(Image[0], Image[0]);
	clahe->apply(Image[1], Image[1]);
	clahe->apply(Image[2], Image[2]);
}
/*........................................... END .................................................*/

/*...................................... MAIN PROGRAM .............................................*/
int main()
{
	// Create Variables to Store Actual Values of [R, G, B] Cheannels.
	// 'Select' Variable f-or selection of The Enhancement Method.  
	// Arrays to store min and max intensities of each channels [R, G, B].
	Mat RGB_Image[3]; int Select; double min[3], max[3];

	// Initialize Clock Variable to compute Time Taken in millisecs
	clock_t start, end;
	float Time_Used;

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

	// Start The Timer
	start = clock();

	// Selection of The Enhancement Method
	switch (Select)
	{
	case 1: printf("You Selected Linear Stretching \n");
		Linear_Stretch(RGB_Image, min, max, Image.rows, Image.cols);
		break;
	case 2: printf("You Selected Piece-Wise Linear Stretching \n");
		PW_Linear_Stretch(RGB_Image, min, max, Image.rows, Image.cols, 5);
		break;
	case 3:	printf("You Selected Logarithimic Stretching \n");
		Log_Stretch(RGB_Image, Image.rows, Image.cols);
		break;
	case 4:	printf("You Selected Exponential Stretching \n");
		Exp_Stretch(RGB_Image, Image.rows, Image.cols);
		break;
	case 5:	printf("You Selected Power-Law Transformation \n");
		Powlaw_Trans(RGB_Image, Image.rows, Image.cols, 0.75, 3.996);
		break;
	case 6:	printf("You Selected Histogram Equalizationn \n");
		Histogram_Equalization(RGB_Image);
		break;
	case 7:	printf("You Selected Adaptive histogram Equalization \n");
		Adaptive_HE(RGB_Image);
		break;
	case 8:	printf("You Selected BBHE \n");
		//LP_Butterworth_Filter(LPFilter, CUTOFF, ord);
		break;
	case 9:	printf("You Selected DSIHE \n");
		//LP_Butterworth_Filter(LPFilter, CUTOFF, ord);
		break;
	case 10: printf("You Selected CLAHE \n");
		CLAH_Equalization(RGB_Image, 4);
		break;
	default: printf("Wrong Selection \n");
		break;
	}

	merge(RGB_Image, 3, Image);
	Image.convertTo(Image, CV_8U);

	//Stop the Timer
	end = clock();

	// Calculate Time Taken for Image Highboosting by a Highboost Filter in millisecs.
	Time_Used = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Time Taken for Image smoothing : %.3f", Time_Used);

	// Display Final Enhanced Image 
	namedWindow("ENHANCED IMAGE", WINDOW_NORMAL);
	imshow("ENHANCED IMAGE", Image);

	// Write 2D Array to Image File (.bmp)
	imwrite("AHE.bmp", Image);

	waitKey(0);
    return 0;
}
/*........................................... END .................................................*/

