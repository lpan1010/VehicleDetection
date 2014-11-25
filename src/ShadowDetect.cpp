/*
 * ShadowDetect.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: lpan
 */

#include "ShadowDetect.h"
#include "utils.h"
#include "LineDetect.h"
#include "LineGrouping.h"
#include "ExtractLine.h"
#include "RectObject.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;
using std::vector;

//------------------------------------------------
//! 构造函数
ShadowDetect::ShadowDetect(){

}

//------------------------------------------------
//! 开始检测车底阴影
vector<RectObject> ShadowDetect::startDetect(Mat &src){
	vector<RectObject> rects;
	//转成灰度图
	Mat src_gray;
	getGrayImg(src, src_gray);
	/**
	 * 求第一遍过滤的阈值
	 */
	double mean = getMean(src_gray);
	double variance = getVariance(src_gray, mean);
	double threshold1 = getThreshold(mean, variance);
	/**
	 * 求第二遍过滤的阈值
	 */
	mean = getMean(src_gray, threshold1);
	variance = getVariance(src_gray, mean, threshold1);
	double threshold2 = getThreshold(mean, variance);
	/**
	 * 根据阈值过滤图片
	 */
	filterByThreshold(src_gray, threshold2);
	/**
	 * 过滤后的图片中检测线段
	 */
	Mat src_line;
	LineDetect ld = LineDetect();
	vector<LineDetect::lineSegment> lines = ld.startDetect(src_gray, src_line);
	/**
	 * 将线段聚成组
	 */
	if(lines.size() != 0){
		cout << "group" << endl;
		Mat src_group = Mat::zeros(src_gray.rows, src_gray.cols, src.type());
		LineGrouping lg = LineGrouping();
		map<int, vector<LineDetect::lineSegment> > lineGroups = lg.startGrouping(lines, src_group);
		/**
		 * 提取车底与路面的边界
		 */
		Mat src_extract = Mat::zeros(src_gray.rows, src_gray.cols, src_gray.type());
		ExtractLine el = ExtractLine();
		map<int, LineDetect::lineSegment> extractLines = el.startExtract(lineGroups, src_extract);
		/**
		 * 在原图上画出边界
		 */
		if(extractLines.size() != 0){
			Mat Img = Mat::zeros(src.rows, src.cols, src.type());
			for(map<int, LineDetect::lineSegment>::iterator k = extractLines.begin(); k != extractLines.end(); k++){
				LineDetect::lineSegment lineseg = k->second;
				int width = lineseg.end.x - lineseg.start.x;
//				int hight = 100;
				int hight = width/2;
//				int hight = width;
				if(lineseg.start.y <= width){
					continue;
				}
				Point top(lineseg.start.x, lineseg.start.y - hight);
				Point bottom(lineseg.end.x, lineseg.end.y);

//				rectangle( src, top, bottom, Scalar( 0, 255, 0 ), 2, 8 );



				Rect roi(top, bottom);
				Mat small(src, roi);
				int count = 0;
				for(int i = 0; i < small.rows; i++){
					for(int j = 0; j < small.cols; j++){
						if(small.at< cv::Vec3b>(i,j)[2]> (small.at<cv::Vec3b>(i,j)[0] + small.at<cv::Vec3b>(i,j)[1])){
							count++;
						}
					}
					if(count > 15){
						line(src_extract, lineseg.start, lineseg.end, Scalar(255, 255, 255 ), 1);
						rectangle( src, top, bottom, Scalar( 0, 255, 0 ), 2, 8 );

						RectObject rb;
						rb.setX(lineseg.start.x);
						rb.setY(lineseg.start.y - hight);
						rb.setWidth(width);
						rb.setHeight(width);
						rects.push_back(rb);
						//如果红点大于阈值不用再循环了
						break;
					}
				}


			}
//			namedWindow("src", 1);
//			imshow( "src", src );
//			namedWindow("img", 1);
//			imshow( "img", Img );
//			namedWindow("src_gray", 1);
//			imshow( "src_gray", src_gray );
//			namedWindow("src_line", 1);
//			imshow( "src_line", src_line );
//			namedWindow("src_group", 1);
//			imshow( "src_group", src_group );
//			namedWindow("src_extract", 1);
//			imshow( "src_extract", src_extract );
//			waitKey (0);
		}
	}
	return rects;
}

//------------------------------------------------
//! 获取图像均值
double ShadowDetect::getMean(Mat &img){
	double mean = 0;
	int nRows = img.rows;
	int nCols = img.cols;
	uchar* p;
	for( int i = 0; i < nRows; ++i){
		p = img.ptr<uchar>(i);
		for ( int j = 0; j < nCols; j = j+1){
			mean = mean + p[j];
		}
	}
	mean = mean/(nRows*nCols);
	return mean;
}

//------------------------------------------------
//! 获取图像均值, 只针对阈值范围内的点
double ShadowDetect::getMean(Mat &img, double threshold){
	double mean = 0;
	int count = 0;
	int nRows = img.rows;
	int nCols = img.cols;
	uchar* p;
	for( int i = 0; i < nRows; ++i){
		p = img.ptr<uchar>(i);
		for ( int j = 0; j < nCols; j = j+1){
			if(threshold >= p[j]){
				mean = mean + p[j];
				count++;
			}
		}
	}
	mean = mean/count;
	return mean;
}

//------------------------------------------------
//!获取图像方差
double ShadowDetect::getVariance(Mat &img, double mean){
	double variance = 0;
	int nRows = img.rows;
	int nCols = img.cols;
	uchar* p;
	for( int i = 0; i < nRows; ++i){
		p = img.ptr<uchar>(i);
		for ( int j = 0; j < nCols; j = j+1){
			variance = variance + (p[j]-mean)*(p[j]-mean);
		}
	}
	variance = sqrt(variance/(nRows*nCols));
	return variance;
}

//------------------------------------------------
//!获取图像方差, 只针对阈值内的点
double ShadowDetect::getVariance(Mat &img, double mean, double threshold){
	double variance = 0;
	int nRows = img.rows;
	int nCols = img.cols;
	int count = 0;
	uchar* p;
	for( int i = 0; i < nRows; ++i){
		p = img.ptr<uchar>(i);
		for ( int j = 0; j < nCols; j = j+1){
			if(threshold >= p[j]){
				variance = variance + (p[j]-mean)*(p[j]-mean);
				count++;
			}
		}
	}
	variance = sqrt(variance/count);
	return variance;
}

//-------------------------------------------------
//!获取阈值
double ShadowDetect::getThreshold(double mean, double variance){
	return mean - variance*(variance/mean);
}

//-------------------------------------------------
//!根据阈值过滤图片
void ShadowDetect::filterByThreshold(Mat &src_filter, double threshold){
	int nRows = src_filter.rows;
	int nCols = src_filter.cols;
	uchar*p;
	for( int i = 0; i < nRows; ++i){
		p = src_filter.ptr<uchar>(i);
		for (int j = 0; j < nCols; j = j+1){
			if(p[j] >= threshold){
				p[j] = 255;
			}
			else{
				p[j] = 0;
			}
		}
	}
}

