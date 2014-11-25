/*
 * Launch.h
 *
 *  Created on: Oct 23, 2014
 *      Author: lpan
 */

#ifndef LAUNCH_H_
#define LAUNCH_H_

using namespace std;

class Launch{

public:
	Launch();
	int mainImage(char*imgPath);
	int mainVideo(char*videoPath);
	int mainMutiImage(char*imgPath);

};


#endif /* LAUNCH_H_ */
