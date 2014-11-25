/*
 * LineGrouping.h
 *
 *  Created on: Oct 23, 2014
 *      Author: lpan
 */

#ifndef LINEGROUPING_H_
#define LINEGROUPING_H_

#include "LineDetect.h"

using namespace cv;
using std::vector;
using namespace std;

class LineGrouping {

public:

	struct group{
		vector<LineDetect::lineSegment> lines;
		int maxLen;//线段组中最长的长度
		int maxIndex;//线段组中最长线段下标
		int maxDiffer;//线段组
	};

	LineGrouping();
	virtual ~LineGrouping();

	map<int, vector<LineDetect::lineSegment> > startGrouping(vector<LineDetect::lineSegment> lines, Mat &src_group);

};

#endif /* LINEGROUPING_H_ */
