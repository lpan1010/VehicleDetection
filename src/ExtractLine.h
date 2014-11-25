/*
 * ExtractLine.h
 *
 *  Created on: Oct 23, 2014
 *      Author: lpan
 */

#ifndef EXTRACTLINE_H_
#define EXTRACTLINE_H_

#include "LineDetect.h"
#include "opencv2/opencv.hpp"

using namespace std;
using std::vector;
using namespace cv;

class ExtractLine {

public:
	ExtractLine();
	virtual ~ExtractLine();
	map<int, LineDetect::lineSegment> startExtract(map<int, vector<LineDetect::lineSegment> > lineGroups, Mat &src_group);
};

#endif /* EXTRACTLINE_H_ */
