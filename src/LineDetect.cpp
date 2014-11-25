/*
 * LineDetect.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: lpan
 */

#include "LineDetect.h"



using namespace cv;
using std::vector;

LineDetect::LineDetect() {
	// TODO Auto-generated constructor stub

}

LineDetect::~LineDetect() {
	// TODO Auto-generated destructor stub
}
/**
 * 检测直线
 */
vector<LineDetect::lineSegment> LineDetect:: startDetect(Mat &src_gray, Mat &src_line){
	//初始化输出图像
	src_line = Mat::zeros(src_gray.rows, src_gray.cols, src_gray.type());
	vector<LineDetect::lineSegment> lines;
	int nRows = src_gray.rows;
	int nCols = src_gray.cols;
	Scalar s(255, 255, 255);
	uchar*p;
	for(int i = nRows/10; i < (nRows*0.8); ++i){
		p = src_gray.ptr<uchar>(i);
		//初始化起点和终点的坐标
		int startx = i, endx = i;
		int starty = -1,endy = -1;
		for (int j = 1; j < nCols - 1; j = j+1){
//			cout << (int)p[j] << ",";
			//检测起点
			if((p[j-1] - p[j]) == 255 && (p[j] - p[j+1]) == 0){
				starty = j;
			}
			//如果起点坐标不为空，并且满足终点的条件
			if(starty != -1 && (p[j] - p[j-1]) == 0 && (p[j+1] - p[j]) == 255){
				endy = j;
//				cout << src_gray.rows << "\t" << src_gray.cols << "\t" << abs(endy - starty) << endl;
				//线段条件
				int length = abs(endy - starty);
				if(endy > starty && length > src_gray.cols/15 && length < src_gray.cols/3){
					lineSegment ls;
					ls.start = Point(starty, startx);
					ls.end = Point(endy, endx);
					ls.length = length;
					lines.push_back(ls);
					line(src_line, ls.start, ls.end, s, 1);
				}
				//一行中可能包含了几条线段，因此在检测到一对起点-终点后，继续检测起点-终点对
				starty = -1;
				endy = -1;
			}
		}
	}
	return lines;
}

