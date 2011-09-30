/*
 *  IKLine.h
 *  Paint
 *
 *  Created by Mario.Gonzalez on 6/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "cinder/Perlin.h"
//#include "cinder/app/AppBasic.h"

#include <list>
#include <vector>

#include "Segment.h"

//using std::list;
//using std::vector;
//using namespace ci;

class IKLine
{
public:
	IKLine(void);
	
	void init();
	void nextFrame(ci::Vec2f toPosition, float damping);
	void drag(  Segment* segment, float xpos, float ypos);
	
	// Properties
	std::vector<Segment*> _segments;
	
	float segmentLength;
	int   segmentNum;
	float x, y;
	float oldX, oldY;
	float gravity, friction;
};
