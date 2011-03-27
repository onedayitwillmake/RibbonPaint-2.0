/*
 *  IKLine.cpp
 *  Paint
 *
 *  Created by Mario.Gonzalez on 6/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "IKLine.h"

static const float degToRad = 57.2957795f;
static const float radToDeg = 0.0174532925f;

IKLine::IKLine()
{
	segmentNum = 8;
	segmentLength = 20;
	gravity = 10;
	friction = 3;
	oldX = oldY = 0;
	x = y = 0.0f;
};

void IKLine::init()
{
	int i = 0;

	Segment* segment = new Segment( 0 * i );
	_segments.push_back( segment );
	
	for (i=1; i < segmentNum; i++)
	{
		Segment* segment = new Segment( (float)segmentLength * ((float)i * 0.45f) );
		_segments.push_back( segment );
	}
}

void IKLine::nextFrame(ci::Vec2f toPosition, float damping)
{
	oldX += (toPosition.x - oldX) * damping;
	oldY += (toPosition.y - oldY) * damping;
	
	drag( _segments[0], oldX, oldY);
	
	for (int i = 1; i < segmentNum; i++)
	{
		Segment* segmentA = _segments[i];
		Segment* segmentB = _segments[i-1];
		drag( segmentA, segmentB->x, segmentB->y );
	}
}

void IKLine::drag( Segment* segment, float xpos, float ypos)
{
	segment->next();
	
	float dx		= xpos - segment->x;
	float dy		= ypos - segment->y;
	segment->angle	= atan2f(dy, dx);
	
	ci::Vec2f pin = segment->getPin();
	float w = pin.x - segment->x;
	float h = pin.y - segment->y;
	
	segment->x = xpos - w;
	segment->y = ypos - h;
	segment->setVector();
	
	segment->vx *= friction;
	segment->vy *= friction;
	segment->vy += gravity;
}
