//
//  detectBlink.h
//  eyeTracker
//
//  Created by Isidoro Navedo on 11/29/16.
//

#ifndef detectBlink_h
#define detectBlink_h

#include <iostream>

bool didBlink(cv::Mat ROI, cv::CascadeClassifier open_eye_cascade, cv::CascadeClassifier eye_cascade);

#endif /* detectBlink_h */
