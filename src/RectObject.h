/*
 * RectObject.h
 *
 *  Created on: Nov 19, 2014
 *      Author: lpan
 */

#ifndef RECTOBJECT_H_
#define RECTOBJECT_H_

class RectObject {

public:

	int x;//起点x坐标
	int y;//起点y坐标
	int width;//矩形宽度
	int height;//矩形高度

	RectObject() : x(-1), y(-1), width(0), height(0) { };

	RectObject(int x, int y, int width, int height);

	//报错 undefined reference to `vtable for RectObject'
//	virtual ~RectObject();

	int getHeight() ;

	void setHeight(int height);

	int getWidth() ;

	void setWidth(int width) ;

	int getX() ;

	void setX(int x);

	int getY() ;

	void setY(int y) ;
};

#endif /* RECTOBJECT_H_ */
