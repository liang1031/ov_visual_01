// ov_visual_01.cpp: 定义控制台应用程序的入口点。
//

// ov_test_01.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
////#include "opencv2/nonfree/nonfree.hpp"    
////#include "opencv2/legacy/legacy.hpp" 
//#include <iostream>
//#include"segment.h"
//#include<string>
//
//void put_text(Mat srcImage,string inputText,  double textNum) {
//	stringstream meanValueStream;
//	string meanValueString;
//	meanValueStream << textNum;
//	meanValueStream >> meanValueString;
//	meanValueString = inputText + meanValueString;
//	putText(srcImage, meanValueString, Point(20, 50), CV_FONT_HERSHEY_COMPLEX, 0.8, Scalar(255, 255, 25), 2);
//	imshow(inputText, srcImage);
//}
//
//int main() {
//	//Mat srcImage = imread("1.bmp");
//	//imshow("src",srcImage);
//	//ostu(srcImage);
//	//waitKey(0);
//	//return 0;
//
//	Mat srcImage = imread("14.bmp");
//	Mat dstImage;
//	Mat greyImage;
//	cvtColor(srcImage, greyImage, CV_RGB2GRAY);
//	//blur(greyImage, dstImage, Size(15, 15));
//	/*imwrite("blur2.bmp",dstImage);*/
//	imshow("greyImage",greyImage);
//	Mat sobelImage;
//	Sobel(greyImage, sobelImage, CV_16U, 0, 1);
//
//	convertScaleAbs(sobelImage, sobelImage);
//	imshow("sobelImage",sobelImage);
//	//图像的平均灰度  
//	double meanValue = 0.0;
//	meanValue = mean(sobelImage)[0];
//
//	//double to string  
//	put_text(srcImage,"Articulation: ",meanValue);
//	waitKey(0);
//	return 0;
//} 
#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>  //头文件
#include <opencv2/xfeatures2d.hpp>
using namespace cv;  //包含cv命名空间
using namespace std;

int main()
{
	//Create SIFT class pointer
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	//读入图片
	Mat img_1 = imread("1.jpg");
	Mat img_2 = imread("2.jpg");
	//Detect the keypoints
	vector<KeyPoint> keypoints_1, keypoints_2;
	f2d->detect(img_1, keypoints_1);
	f2d->detect(img_2, keypoints_2);
	//Calculate descriptors (feature vectors)
	Mat descriptors_1, descriptors_2;
	f2d->compute(img_1, keypoints_1, descriptors_1);
	f2d->compute(img_2, keypoints_2, descriptors_2);
	//Matching descriptor vector using BFMatcher
	BFMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);
	//绘制匹配出的关键点
	Mat img_matches;
	drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_matches);
	imshow("【match图】", img_matches);
	//等待任意按键按下
	waitKey(0);
}

//void match(Mat srcImage, Mat matchImage) {
//	GoodFeaturesToTrackDetector Detector(500);  //最大点数,值越大，点越多
//	vector<KeyPoint> keyPoint1, keyPoint2;
//	Detector.detect(srcImage, keyPoint1);
//	Detector.detect(matchImage, keyPoint2);
//
//	//特征点描述，为下边的特征点匹配做准备    
//	SiftDescriptorExtractor  Descriptor;
//	Mat imageDesc1, imageDesc2;
//	Descriptor.compute(srcImage, keyPoint1, imageDesc1);
//	Descriptor.compute(matchImage, keyPoint2, imageDesc2);
//
//	BruteForceMatcher< L2<float> > matcher;
//	vector<vector<DMatch> > matchePoints;
//	vector<DMatch> GoodMatchePoints;
//
//	vector<Mat> train_desc(1, imageDesc1);
//	matcher.add(train_desc);
//	matcher.train();
//
//	matcher.knnMatch(imageDesc2, matchePoints, 2);
//	cout << "total match points: " << matchePoints.size() << endl;
//
//	for (int i = 0; i < matchePoints.size(); i++)
//	{
//		if (matchePoints[i][0].distance < 0.6 * matchePoints[i][1].distance)
//		{
//			GoodMatchePoints.push_back(matchePoints[i][0]);
//		}
//	}
//
//	Mat first_match;
//	drawMatches(matchImage, keyPoint2, srcImage, keyPoint1, GoodMatchePoints, first_match);
//	imshow("first_match ", first_match);
//}

