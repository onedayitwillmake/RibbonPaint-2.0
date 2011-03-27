/*
 *  Segment.cpp
 *  Paint
 *
 *  Created by Mario.Gonzalez on 6/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Segment.h"
using namespace ci;

Segment::Segment(float length)
{
	segmentLength = length;
	
	angle = 0.0f;
	x = Rand::randFloat(1.0f, 1.5f);
	y = Rand::randFloat(1.0f, 1.5f);

	vx = Rand::randFloat(0.0f, 1.0f); 
	vy = Rand::randFloat(0.0f, 1.0f);
	prevX = Rand::randFloat(0.0f, 1.0f);
	prevX = Rand::randFloat(0.0f, 1.0f);
};

void Segment::next()
{
	x += vx;
	y += vy;
}

void Segment::setVector()
{
	if(prevX && prevY) 
	{
		vx += ((x - prevX) - vx) * 0.98f;
		vy += ((y - prevY) - vy) * 0.98f;
	}
	prevX = x;
	prevY = y;
}


Vec2f Segment::getPin()
{
	float xpos = x + cosf( angle ) * segmentLength;
	float ypos = y + sinf( angle ) * segmentLength;
	
	return Vec2f(xpos, ypos);
}
