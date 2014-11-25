/*
 * ExtractLine.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: lpan
 */

#include "ExtractLine.h"
#include "LineDetect.h"

#include <iostream>
#include<algorithm>

using namespace std;
using std::vector;

ExtractLine::ExtractLine() {
	// TODO Auto-generated constructor stub

}

ExtractLine::~ExtractLine() {
	// TODO Auto-generated destructor stub
}

/**
 * 从线段组中抽取若干线段
 */
map<int, LineDetect::lineSegment> ExtractLine::startExtract(map<int, vector<LineDetect::lineSegment> > lineGroups, Mat &src_extract){


	vector<LineDetect::lineSegment> extractLines;
	Scalar s(255, 255, 255);
	map<int, vector<LineDetect::lineSegment> >::iterator group_iter;
	cout << "group size: " << lineGroups.size() << endl;
	for(group_iter = lineGroups.begin(); group_iter != lineGroups.end(); group_iter++){
		vector<LineDetect::lineSegment> glines = group_iter->second;
		//如果组内的线段个数超过5条, 把组内第一条线段放入代表直线数组中去。
		if(glines.size() > 5){
			int max_index = 0;
			int max_len = abs(glines[0].end.x - glines[0].start.x);
			for(vector<LineDetect::lineSegment>::size_type i = 0; i < glines.size(); i++){
				int len = abs(glines[i].end.x - glines[i].start.x);
				if(max_len < len){
					max_len = len;
					max_index = i;
				}
			}
			extractLines.push_back(glines[max_index]);
//			line(src_group, glines[max_index].start, glines[max_index].end, s, 1);
		}
	}
	cout << "extractLines: " <<  extractLines.size() << endl;

	map<int, LineDetect::lineSegment> extractLines2;
	if(extractLines.size() != 0){
		for(vector<LineDetect::lineSegment>::size_type i = 0; i < extractLines.size(); i++){
			extractLines2[i] = extractLines[i];
		}
		vector<LineDetect::lineSegment>::iterator it;
		for(vector<LineDetect::lineSegment>::size_type i = 0; i < extractLines.size() - 1; i++){
			LineDetect::lineSegment LA = extractLines[i];
			for(vector<LineDetect::lineSegment>::size_type j = i+1; j < extractLines.size(); j++){
				LineDetect::lineSegment LB = extractLines[j];
				int horizonDistance = max((LA.start.x - LB.end.x), (LB.start.x - LA.end.x));
				if(abs(LA.start.y - LB.start.y) < 40 && horizonDistance < 0){
					for(map<int, LineDetect::lineSegment>::iterator k = extractLines2.begin(); k != extractLines2.end(); ){
						if(k->first == j){
							extractLines2.erase(k++);
						}
						else{
							k++;
						}
					}
				}
			}
		}
		cout << "extractLines2: " <<  extractLines2.size() << endl;
		return extractLines2;
	}

	else{
		return extractLines2;
	}

}
