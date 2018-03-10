#pragma once
#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

void find_contours(Mat ostuImage);
void ostu(Mat srcImage);

#endif // !SEGMENT_H_

