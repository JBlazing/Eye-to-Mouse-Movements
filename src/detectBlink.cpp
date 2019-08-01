//
//  detectBlink.cpp
//  eyeTracker
//
//  Created by Isidoro Navedo on 11/29/16.
//

#include <ctime>
#include <opencv2/objdetect/objdetect.hpp>

#include "detectBlink.h"

bool didBlink(cv::Mat ROI, cv::CascadeClassifier eye_cascade, cv::CascadeClassifier open_eye_cascade)
{
    // Detect eye.
    std::vector<cv::Rect> eye;
    eye_cascade.detectMultiScale(ROI, eye);

    if (eye.size() > 0)
    {
        std::time_t time = std::time(NULL);
        std::cout << std::ctime(&time);
        std::cout << "Eye detected" << std::endl;

        // Detect open eye.
        std::vector<cv::Rect> eyeOpen;
        open_eye_cascade.detectMultiScale(ROI, eyeOpen);

        if (eyeOpen.size() > 0)
        {
            // Eye is open.
            std::cout << "Eye open" << std::endl;
            return false;
        }
        else
        {
            // Eye is closed.
            std::cout << "Eye closed" << std::endl;
            return true;
        }
    }
    else { return false; }
}
