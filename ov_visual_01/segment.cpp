#include "stdafx.h"
#include"segment.h"

void find_contours(Mat ostuImage) {

	Mat dstImage = Mat::zeros(ostuImage.rows, ostuImage.cols, CV_8UC3);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(ostuImage, contours, hierarchy,
		CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	int index = 0;
	double area;
	Scalar color(255, 255, 255);
	for (; index >= 0; index = hierarchy[index][0])
	{
		area = contourArea(contours[index]);
		if (area > 25) {
			drawContours(dstImage, contours, index, color, CV_FILLED, 8, hierarchy);
		}

	}
	imshow("ÂÖÀªÍ¼", dstImage);
}

void ostu(Mat srcImage) {
	Mat grayImage, ostuImage;
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	imshow("gray", grayImage);
	threshold(grayImage, ostuImage, 0, 255, CV_THRESH_OTSU);
	imshow("ostu", ostuImage);
	find_contours(ostuImage);
}
