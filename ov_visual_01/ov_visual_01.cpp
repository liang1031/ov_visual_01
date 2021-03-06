// ov_visual_01.cpp: 定义控制台应用程序的入口点。
//
//#include "stdafx.h"
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
////
//int main() {
//	Mat srcImage = imread("14.bmp");
//	Mat dstImage;
//	Mat greyImage;
//	cvtColor(srcImage, greyImage, CV_RGB2GRAY);
//	//blur(greyImage, dstImage, Size(15, 15));
//	/*imwrite("blur2.bmp",dstImage);*/
//	imshow("greyImage",greyImage);
//	Mat sobelImage;
//	Sobel(greyImage, sobelImage, CV_16U, 1, 1);
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
#include"stdafx.h"
#include <iostream>    
#include "opencv2/core.hpp"  
//#include "opencv2/core/utility.hpp"  
//#include "opencv2/core/ocl.hpp"  
#include "opencv2/imgcodecs.hpp"  
#include "opencv2/highgui.hpp"  
#include "opencv2/features2d.hpp"  
#include "opencv2/calib3d.hpp"  
#include "opencv2/imgproc.hpp"  
//#include"opencv2/flann.hpp"  
#include"opencv2/xfeatures2d.hpp"  
//#include"opencv2/ml.hpp"  

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;
//using namespace cv::ml;

int main()
{
	//Mat a = imread("book1.jpg", IMREAD_GRAYSCALE);    //读取灰度图像  
	//Mat b = imread("book2.jpg", IMREAD_GRAYSCALE);
	Mat srcMatch = imread("14_little.bmp");    //读取灰度图像  
	Mat srcMatched = imread("all.bmp");
	if (srcMatch.empty() || srcMatched.empty()) {
		cout << "empty..." << endl;
		return -1;
	}
	Ptr<SURF> surf = SURF::create(800);
	BFMatcher matcher;
	Mat grayMatch, grayMatched;
	cvtColor(srcMatch,grayMatch,CV_RGB2GRAY);
	//imshow("grayMatch",grayMatch);
	cvtColor(srcMatched, grayMatched, CV_RGB2GRAY);
	//imshow("grayMatched", grayMatched);

	Mat dstMatch, dstMatched;
	vector<KeyPoint>key1, key2;
	vector<DMatch> matches;
	surf->detectAndCompute(grayMatch, Mat(), key1, dstMatch);
	surf->detectAndCompute(grayMatched, Mat(), key2, dstMatched);
	matcher.match(dstMatch, dstMatched, matches);       //匹配  
	std::cout << matches.size() << std::endl;
	sort(matches.begin(), matches.end());  //筛选匹配点  
	vector<DMatch> good_matches;
	int ptsPairs = std::min(50, (int)(matches.size() * 0.5));//0.15  0.5
	cout << ptsPairs << endl;
	for (int i = 0; i < ptsPairs; i++)
	{
		good_matches.push_back(matches[i]);
	}
	Mat dstImage;
	//绘制匹配点  
	drawMatches(srcMatch, key1, srcMatched, key2, good_matches, dstImage,
		Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS); 
	//输出匹配点坐标
	vector<Point2f> object,scene;
	for (int i = 0; i < good_matches.size(); ++i) {
		object.push_back(key1[good_matches[i].queryIdx].pt);
		scene.push_back(key2[good_matches[i].trainIdx].pt);
		cout << object[i].x << ":" << object[i].y <<"  "
			 << scene[i].x << ":" << scene[i].y << endl;

	}
	imshow("match image:", dstImage);
	//std::vector<Point2f> obj;
	//std::vector<Point2f> scene;

	//for (size_t i = 0; i < good_matches.size(); i++)
	//{
	//	obj.push_back(key1[good_matches[i].queryIdx].pt);
	//	scene.push_back(key2[good_matches[i].trainIdx].pt);
	//}

	//std::vector<Point2f> obj_corners(4);
	//obj_corners[0] = Point(0, 0);
	//obj_corners[1] = Point(a.cols, 0);
	//obj_corners[2] = Point(a.cols, a.rows);
	//obj_corners[3] = Point(0, a.rows);
	//std::vector<Point2f> scene_corners(4);

	//Mat H = findHomography(obj, scene, RANSAC);      //寻找匹配的图像  
	//perspectiveTransform(obj_corners, scene_corners, H);

	//line(outimg, scene_corners[0] + Point2f((float)a.cols, 0), scene_corners[1] + Point2f((float)a.cols, 0), Scalar(0, 255, 0), 2, LINE_AA);       //绘制  
	//line(outimg, scene_corners[1] + Point2f((float)a.cols, 0), scene_corners[2] + Point2f((float)a.cols, 0), Scalar(0, 255, 0), 2, LINE_AA);
	//line(outimg, scene_corners[2] + Point2f((float)a.cols, 0), scene_corners[3] + Point2f((float)a.cols, 0), Scalar(0, 255, 0), 2, LINE_AA);
	//line(outimg, scene_corners[3] + Point2f((float)a.cols, 0), scene_corners[0] + Point2f((float)a.cols, 0), Scalar(0, 255, 0), 2, LINE_AA);

	cvWaitKey(0);
	return 0;
}



//#include "stdafx.h"
//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <opencv2/features2d.hpp>
//
//using namespace cv;
//
//int main()
//{
//	Ptr<ORB> f2d = ORB::create();
//	Mat img_1 = imread("14_little.bmp");
//	Mat img_2 = imread("all_little.bmp");
//	/*Mat img_1 = imread("book1.jpg");
//	Mat img_2 = imread("book2.jpg");*/
//
//	Mat grayImage1;
//	cvtColor(img_1, grayImage1, CV_BGR2GRAY);
//	Mat grayImage2;
//	cvtColor(img_2, grayImage2, CV_BGR2GRAY);
//
//	//Detect the keypoints
//	std::vector<KeyPoint> keypoints_1, keypoints_2;
//	f2d->detect(grayImage1, keypoints_1);
//	f2d->detect(grayImage2, keypoints_2);
//	//Calculate descriptors (feature vectors)
//	Mat descriptors_1, descriptors_2;
//	f2d->compute(grayImage1, keypoints_1, descriptors_1);
//	f2d->compute(grayImage2, keypoints_2, descriptors_2);
//	//Matching descriptor vector using BFMatcher
//	BFMatcher  matcher;
//	std::vector<DMatch> matches;
//	matcher.match(descriptors_1, descriptors_2, matches);
//	//绘制匹配出的关键点
//	Mat img_matches;
//	drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_matches);
//	imshow("【match图】", img_matches);
//	//等待任意按键按下
//	waitKey(0);
//}



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

