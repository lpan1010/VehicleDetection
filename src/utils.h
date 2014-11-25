
#ifndef UTILS_H
#define UTILS_H

#include <opencv2/opencv.hpp>
#include <cv.h>
#include <vector>

using namespace cv;

//! Display error message and terminate program
void error(const char *msg);

//! Show the provided image and wait for keypress
void showImage(const IplImage *img);

void showImage(char*title, Mat img);

//! Show the provided image in titled window and wait for keypress
void showImage(char *title,const IplImage *img);

// Convert image to single channel 32F
IplImage* getGray(const IplImage *img);

//! Round float to nearest integer
inline int fRound(float flt)
{
  return (int) floor(flt+0.5f);
}

void getGrayImg(Mat&src, Mat&src_gray);

#endif
