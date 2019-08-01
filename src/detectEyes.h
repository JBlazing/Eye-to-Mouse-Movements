#ifndef __DEYES__
#define __DEYES__
#include "constants.h"
#include "findEyeCenter.h"
#include "findEyeCorner.h"
#include "mouse.h"

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>


/** Function Headers */
void detectAndDisplay( cv::Mat frame , int* , int* );
void findEyes(cv::Mat frame_gray, cv::Rect face , int *LeftPupil , int* RightPupil);
cv::Mat findSkin (cv::Mat &frame);

/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
cv::String face_cascade_name = "../res/haarcascade_frontalface_alt.xml";
cv::CascadeClassifier face_cascade;
std::string main_window_name = "Capture - Face detection";
std::string face_window_name = "Capture - Face";
cv::RNG rng(12345);
cv::Mat debugImage;
cv::Mat skinCrCbHist = cv::Mat::zeros(cv::Size(256, 256), CV_8UC1);

#endif

