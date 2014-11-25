/*
 * GaussFilter.cpp
 *
 *  Created on: Oct 21, 2014
 *      Author: lpan
 */

#include "GaussFilter.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

GaussFilter::GaussFilter() {
	// TODO Auto-generated constructor stub

}

GaussFilter::~GaussFilter() {
	// TODO Auto-generated destructor stub
}

void GaussFilter::filter(Mat &src_gray, Mat &src_gauss){
	GaussianBlur(src_gray, src_gauss, Size(21, 21), 0, 0);//高斯滤波
}

