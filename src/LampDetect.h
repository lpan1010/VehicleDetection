/*
 * LampDetect.h
 *
 *  Created on: Oct 28, 2014
 *      Author: lpan
 */

#ifndef LAMPDETECT_H_
#define LAMPDETECT_H_

#include "opencv2/opencv.hpp"

using namespace cv;

class LampDetect {
public:
	LampDetect();
	virtual ~LampDetect();

	void extractRed(Mat & src, Mat & dst);
};

#endif /* LAMPDETECT_H_ */
