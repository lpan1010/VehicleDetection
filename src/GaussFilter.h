/*
 * GaussFilter.h
 *
 *  Created on: Oct 21, 2014
 *      Author: lpan
 */

#ifndef GAUSSFILTER_H_
#define GAUSSFILTER_H_

#include "opencv2/opencv.hpp"

using namespace cv;

class GaussFilter {
public:
	GaussFilter();
	virtual ~GaussFilter();
	void filter(Mat &src_gray, Mat &src_gauss);
};

#endif /* GAUSSFILTER_H_ */
