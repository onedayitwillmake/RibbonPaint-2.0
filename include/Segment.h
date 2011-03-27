/*
 *  Segment.h
 *  Paint
 *
 *  Created by Mario.Gonzalez on 6/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "cinder/Vector.h"
#include "cinder/Rand.h"

class Segment
{
public:
	Segment(float length);
	
	void next();
	void setVector();
	ci::Vec2f getPin();
	
	float segmentLength;
	float x, y;	
	float vx, vy;
	float prevX, prevY;
	float angle;
};