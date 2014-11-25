/*
 * Launch.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: lpan
 */


#include "Launch.h"
#include "ShadowDetect.h"
#include "RectObject.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;
/**
 * PROCEDURE = 1 image
 * PROCEDURE = 2 video
 * PROCEDURE = 3 image path
 */
#define PROCEDURE 3

Launch::Launch(){

}

int Launch::mainImage(char*imgPath){
	Mat src;
//	if(imgPath->is)
	// 装载图像
	src = imread(imgPath);
	if( !src.data ){
		cout << "no picture" << endl;
		return -1;
	}
	ShadowDetect sd = ShadowDetect();
	sd.startDetect(src);
	return 0;
}

int Launch::mainMutiImage(char*imgPathFile){

	ifstream infile;
	infile.open(imgPathFile);
	string dir = "/home/lpan/workspace/computervision/casacdeTest/extract";
	if(!infile){
		cerr << "error: unable to open input file." << imgPathFile << endl;
	}
	string s;
	while(getline(infile, s)){
		stringstream ss;
		ss << dir << "/" << s;
		string impath = ss.str().c_str();
		Mat src = imread(impath);
		cout <<  src.rows << "\t" << src.cols << "\t" <<  impath << endl;
	}
	return 0;
}

int Launch::mainVideo(char*videoPath){
	Mat src,src_gray;
	Launch launch;
	VideoCapture video;
	if(!video.open(videoPath)){
		return 1;
	}
	int i = 1;

	ofstream fout("/home/lpan/workspace/computervision/resource/detect.txt");
	for(;;){

		 video>>src;
		 if(src.empty()){
			 break;
		 }
		 ShadowDetect sd = ShadowDetect();
//		 resize(src, src , Size(800, 450));
		 vector<RectObject> rects = sd.startDetect(src);
		 if(!rects.empty()){
			 stringstream ss;
			 ss << i << ".jpg ";
			 for(vector<RectObject>::size_type i = 0; i < rects.size(); i++){
				 ss << rects[i].x << "," << rects[i].y << "," << rects[i].width << "," << rects[i].height << " ";
			 }
			 fout << ss.str().c_str() << endl;
			 cout << ss.str().c_str() << endl;
		 }

//		 if(i % 2 == 0){
//			 stringstream ss;
//			 ss << "/home/lpan/workspace/computervision/resource/testImage/night/" << i/2 << ".jpg";
//			 imwrite(ss.str().c_str(), src);
//			 cout << i << endl;
//		 }
		 i++;
		 imshow("video",src);
		 waitKey(1);
	}
	return 0;
}


int main(int argc, char**argv) {
	Launch launch = Launch();
	if(PROCEDURE == 1){
		return launch.mainImage(argv[1]);
	}
	else if(PROCEDURE == 2){
		return launch.mainVideo(argv[1]);
	}
	else if(PROCEDURE == 3){
		return launch.mainMutiImage("/home/lpan/workspace/computervision/casacdeTest/extract.txt");
	}
	else{
		cout << "parameter invalid" << endl;
	}
}



