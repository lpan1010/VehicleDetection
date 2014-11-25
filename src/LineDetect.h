/*
 * LineDetect.h
 *
 *  Created on: Oct 23, 2014
 *      Author: lpan
 */

#ifndef LINEDETECT_H_
#define LINEDETECT_H_

#include "opencv2/opencv.hpp"

using namespace cv;
using std::vector;

class LineDetect {

public:
	LineDetect();
	virtual ~LineDetect();

	struct lineSegment{
		Point start;
		Point end;
		int length;
	};

	vector<lineSegment> startDetect(Mat &src_gray, Mat &src_line);
};

#endif /* LINEDETECT_H_ */
