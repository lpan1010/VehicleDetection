/*
 * LampDetect.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: lpan
 */

#include "LampDetect.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

LampDetect::LampDetect() {
	// TODO Auto-generated constructor stub

}

LampDetect::~LampDetect() {
	// TODO Auto-generated destructor stub
}

void LampDetect::extractRed(Mat & src, Mat & dst){
	Mat planes[3];
	split(src,planes);
	dst = planes[0];
}


//int main(int argc, char**argv) {
////	Mat src = imread("/home/lpan/workspace/computervision/resource/rr/1234.jpg", 1), src_HSV;
////	cvtColor( src, src_HSV, COLOR_BGR2HSV );
////	Mat H, S, V;
////	cvSplit( src_HSV, H, S, V, NULL);
////	Mat dst;
////	LampDetect ld = LampDetect();
////	ld.extractRed(src, dst);
//
////	int nRows = dst.rows;
////	int nCols = dst.cols;
////	uchar* p;
////	for( int i = 0; i < nRows; ++i){
////		p = dst.ptr<uchar>(i);
////		for ( int j = 0; j < nCols; j = j+1){
////			if(p[j] > 200){
////				p[j] = 0;
////			}
////		}
////	}
//
//
//	Mat Img=imread("/home/lpan/workspace/computervision/resource/rr/1234.jpg",1);
//	Mat ImgResult = Mat::zeros(Img.rows, Img.cols, Img.type());
//
//	/*過濾紅色(BGR排列)*/
//	for(int i=0;i<Img.rows;i++){
//	  for(int j=0;j<Img.cols;j++){
//		  //如果红色channel占的多
//	     if(Img.at<cv::Vec3b>(i,j)[2] >
//	          (Img.at<cv::Vec3b>(i,j)[0] + Img.at<cv::Vec3b>(i,j)[1]))
//	     {
//	        ImgResult.at<cv::Vec3b>(i,j)[2]=255;
//	     }
//	     else
//	     {
//	        ImgResult.at<cv::Vec3b>(i,j)[0]=0;
//	        ImgResult.at<cv::Vec3b>(i,j)[1]=0;
//	        ImgResult.at<cv::Vec3b>(i,j)[2]=0;
//
//	     }
//	  }
//	}
//	cv::imshow("Img",Img);
//	cv::imshow("ImgResult",ImgResult);
//	cv::waitKey(0);
//
////	namedWindow("src", 1);
////	imshow( "src", src );
////	namedWindow("src_HSV", 1);
////	imshow( "src_HSV", src_HSV );
////	waitKey (0);
//	return 0;
//}

