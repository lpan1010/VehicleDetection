/*
 * RectObject.cpp
 *
 *  Created on: Nov 19, 2014
 *      Author: lpan
 */

#include "RectObject.h"

RectObject::RectObject(int x, int y, int width, int height){
	RectObject::x = x;
	RectObject::y = y;
	RectObject::width = width;
	RectObject::height = height;
}

int RectObject::getHeight() {
	return RectObject::height;
}

void RectObject::setHeight(int height){
	RectObject::height = height;
}

int RectObject::getWidth(){
	return RectObject::width;
}

void RectObject::setWidth(int width){
	RectObject::width = width;
}

int RectObject::getX(){
	return RectObject::x;
}

void RectObject::setX(int x){
	RectObject::x = x;
}

int RectObject::getY(){
	return RectObject::y;
}

void RectObject::setY(int y){
	RectObject::y = y;
}


