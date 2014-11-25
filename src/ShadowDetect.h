/*
 * ShadowDetect.h
 *
 *  Created on: Oct 23, 2014
 *      Author: lpan
 */

#ifndef SHADOWDETECT_H_
#define SHADOWDETECT_H_

#include <opencv2/opencv.hpp>
#include "RectObject.h"

using namespace cv;

class ShadowDetect{

public:
	ShadowDetect();

	vector<RectObject> startDetect(Mat &src);

	double getMean(Mat &img);

	double getMean(Mat &img, double threshold);

	double getVariance(Mat &img, double mean);

	double getVariance(Mat &img, double mean, double threshold);

	double getThreshold(double mean, double variance);

	void filterByThreshold(Mat &img_filter, double threshold);

};



#endif /* SHADOWDETECT_H_ */
