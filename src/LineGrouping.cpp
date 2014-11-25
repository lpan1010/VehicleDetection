/*
 * LineGrouping.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: lpan
 */

#include "LineGrouping.h"
#include "LineDetect.h"

#include <iostream>
#include<algorithm>

using namespace std;
using std::vector;

LineGrouping::LineGrouping() {
	// TODO Auto-generated constructor stub

}

LineGrouping::~LineGrouping() {
	// TODO Auto-generated destructor stub
}

map<int, vector<LineDetect::lineSegment> > LineGrouping::startGrouping(vector<LineDetect::lineSegment> lines, Mat &src_group){
	Scalar s(255, 255, 255);
	map<int, vector<LineDetect::lineSegment> >  lineGroups;
	map<int, int> groupID_index;
	map<int, int> ::iterator indexA, indexB, index_it;
	cout << "line size: " << lines.size() << endl;

	if(lines.size() == 0){
		return lineGroups;
	}

	int groupCount = 1;
	int yThreshold = 200;
	int xThreshold = 50;
	int ydd = 0;//y direction distance, y方向上的距离
	int xdd = 0;//x direction distance, x方向上的距离

	for(vector<LineDetect::lineSegment>::size_type i = 0; i < lines.size() - 1; i++){
		for(vector<LineDetect::lineSegment>::size_type j = i+1; j < lines.size(); j++){
			ydd = 0, xdd = 0;
			LineDetect::lineSegment lineA = lines[i];
			LineDetect::lineSegment lineB = lines[j];
			ydd = abs(lineA.start.y - lineB.start.y);
			xdd = max((lineA.start.x - lineB.end.x), (lineB.start.x - lineA.end.x));
			//如果在y方向上相差不远，并且两条直线在x方向上是相交的
			if(ydd <= yThreshold && xdd < xThreshold){
				indexA = groupID_index.find(i);
				indexB = groupID_index.find(j);
				//如果两条线段都没有分到组中,创建一个新组
				if(indexA == groupID_index.end() && indexB == groupID_index.end()){
					vector<LineDetect::lineSegment> group;
					group.push_back(lineA);
					group.push_back(lineB);
					groupID_index[i] = groupCount;
					groupID_index[j] = groupCount;
					lineGroups[groupCount] = group;
					groupCount++;
				}
				//如果线段A属于某组，将B加入该组中
				else if(indexA != groupID_index.end() && indexB == groupID_index.end()){
					int groupID = groupID_index[i];
					vector<LineDetect::lineSegment> group = lineGroups[groupID];
					group.push_back(lineB);
					lineGroups[groupID] = group;
					groupID_index[j] = groupID;
				}
				//如果线段B属于某组，将A加入该组中
				else if(indexA == groupID_index.end() && indexB != groupID_index.end()){
					int groupID = groupID_index[j];
					vector<LineDetect::lineSegment> group = lineGroups[groupID];
					group.push_back(lineA);
					lineGroups[groupID] = group;
					groupID_index[i] = groupID;
				}
			}
		}
	}
	cout << "group size: " << lineGroups.size() << endl;














//	for(vector<LineDetect::lineSegment>::size_type i = 0; i < lines.size() - 1; i++){
//		LineDetect::lineSegment lineA = lines[i];
//		index_it = groupID_index.find(i);
//		//如果没有被分过组，创建一个组, 将lineA放入组中，同时标识lineA放在了groupCount组
//		if(index_it == groupID_index.end()){
//			vector<LineDetect::lineSegment> group;
//			group.push_back(lineA);
//			groupID_index[i] = groupCount;
//			for(vector<LineDetect::lineSegment>::size_type j = i+1; j < lines.size(); j++){
//				LineDetect::lineSegment lineB = lines[j];
//				//如果线段B已经分组了，不再继续分组
//				index_it = groupID_index.find(j);
//				if(index_it != groupID_index.end()){
//					continue;
//				}
//				//高度相差n个像素以内的，合并直线
////				cout << lineA.start.y << "\t\t" << lineA.end.y << endl;
////				cout << "distance Y: " <<  abs(lineA.start.y - lineB.start.y) << endl;
//				if(abs(lineA.start.y - lineB.start.y) <= yThreshold){
//					//水平上没有重合的两条直线不能合在一组
//					int horizonDistance = max((lineA.start.x - lineB.end.x), (lineB.start.x - lineA.end.x));
////					cout << "horizonDistance: "  << horizonDistance << "\t"<< lineA.start << "\t" << lineA.end << "\t" << lineB.start << "\t" << lineB.end << endl;
//					if(horizonDistance < 0){
//						group.push_back(lineB);
//						groupID_index[j] = groupCount;
//					}
//				}
//			}
//			lineGroups[groupCount] = group;
//			groupCount++;
//		}
//		else{
//			vector<LineDetect::lineSegment> group = lineGroups[groupID_index[i]];
//			for(vector<LineDetect::lineSegment>::size_type j = i+1; j < lines.size(); j++){
//				LineDetect::lineSegment lineB = lines[j];
//				index_it = groupID_index.find(j);
//				if(index_it != groupID_index.end()){
//					continue;
//				}
//				//高度相差n个像素以内的，合并直线
//				if(abs(lineA.start.y - lineB.start.y) <= yThreshold ){
//					int horizonDistance = max((lineA.start.x - lineB.end.x), (lineB.start.x - lineA.end.x));
////					cout << "horizonDistance: " << lineA.start << "\t" << lineA.end << "\t" << lineB.start << "\t" << lineB.end << endl;
//					if(horizonDistance < 0){
//						group.push_back(lineB);
//						groupID_index[j] = groupCount;
//					}
//				}
//			}
//			lineGroups[groupID_index[i]] = group;
//		}
//	}

	/**
	 * 在图片上画出
	 */
//	Scalar s(255, 255, 255);
	map<int, vector<LineDetect::lineSegment> >::iterator group_iter;
	int count = 10;
	for(group_iter = lineGroups.begin(); group_iter != lineGroups.end(); group_iter++){
		Scalar ss(255 - count*2, 255 - count*2, 255 - count*2);
		vector<LineDetect::lineSegment> glines = group_iter->second;
		for(vector<LineDetect::lineSegment>::size_type i = 0; i < glines.size(); i++){
			line(src_group, glines[i].start, glines[i].end, ss, 1);
		}
		count = count + 20;
	}

	return lineGroups;
}

