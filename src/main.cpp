#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>

#include "constants.h"
#include "findEyeCenter.h"
#include "findEyeCorner.h"
#include "mouse.h"


/** Constants **/





void getScreenCorn(CvCapture * cam , int **MaxMin)
{
	cv::Mat frame;
	cout << "look at the top left of the screen then hit enter";
	
	do{
	int c = cv::waitKey(10);
	}while(c == '\n');
	
	frame = cvQueryFrame( capture );
	
	
	cout << "look at the bottom right of the screen then hit enter;
	do{
	c = cv::waitKey(10);
	}while(c == '\n');


}



/**
 * @function main
 */
int main( int argc, const char** argv ) {
  cv::Mat frame;

  // Load the cascades
  if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade, please change face_cascade_name in source code.\n"); return -1; };

  cv::namedWindow(main_window_name,CV_WINDOW_NORMAL);
  cv::moveWindow(main_window_name, 400, 100);
  cv::namedWindow(face_window_name,CV_WINDOW_NORMAL);
  cv::moveWindow(face_window_name, 10, 100);
  cv::namedWindow("Right Eye",CV_WINDOW_NORMAL);
  cv::moveWindow("Right Eye", 10, 600);
  cv::namedWindow("Left Eye",CV_WINDOW_NORMAL);
  cv::moveWindow("Left Eye", 10, 800);
  cv::namedWindow("aa",CV_WINDOW_NORMAL);
  cv::moveWindow("aa", 10, 800);
  cv::namedWindow("aaa",CV_WINDOW_NORMAL);
  cv::moveWindow("aaa", 10, 800);
	int *rightPupils = new int[2];
	int	*leftPupils = new int[2];
	int *last = new int[2];
	int *lastRight = new int[2];
	int *lastLeft = new int[2];
	int **MaxMin values = new int*[2];
	for(int i = 0 ; i < 2 ; i++)
	{
		MaxMin[i] = new int[2];
	}
  createCornerKernels();
  ellipse(skinCrCbHist, cv::Point(113, 155.6), cv::Size(23.4, 15.2),
          43.0, 0.0, 360.0, cv::Scalar(255, 255, 255), -1);
	unsigned long frameNum = 0;
	setDefaultPosition(last);
	
  // I make an attempt at supporting both 2.x and 3.x OpenCV
#if CV_MAJOR_VERSION < 3
  CvCapture* capture = cvCaptureFromCAM( -1 );
  if( capture ) {
  	
  	getScreenCorn(capture , MaxMin );
  	
  	
    while( true ) {
      frame = cvQueryFrame( capture );
#else
  cv::VideoCapture capture(-1);
  if( capture.isOpened() ) {
    while( true ) {
      capture.read(frame);
#endif
	  
      // mirror it
      cv::flip(frame, frame, 1);
      frame.copyTo(debugImage);

      // Apply the classifier to the frame
      if( !frame.empty() ) {
        detectAndDisplay( frame , rightPupils , leftPupils );
        if(frameNum % 2 )moveMouse(leftPupils , rightPupils , last);
        
      }
      else {
        printf(" --(!) No captured frame -- Break!");
        break;
      }
      
     

      imshow(main_window_name,debugImage);

      int c = cv::waitKey(10);
      if( (char)c == 'c' ) { break; }
      if( (char)c == 'f' ) {
        imwrite("frame.png",frame);
      }
		frameNum++;
    }
  }
	delete[] rightPupils;
	delete[] leftPupils;
	delete[] last;
	delete[] lastLeft;
	delete[] lastRight;
	delete[] MaxMin[0];
	delete[] MaxMin[1];
	delete[] MaxMin;
  releaseCornerKernels();

  return 0;
}





