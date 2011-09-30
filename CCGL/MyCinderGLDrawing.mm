//
//  MyCinderGLDrawing.mm
//  CCGLBasic example
//
//  Created by Matthieu Savary on 03/03/11.
//  Copyright (c) 2011 SMALLAB.ORG. All rights reserved.
//
//  More info on the CCGL project >> http://www.smallab.org/code/ccgl/
//  License & disclaimer >> see license.txt file included in the distribution package
//

#import "MyCinderGLDrawing.h"
#define __RIBBON__PAINT__XCODE__ 1

@implementation MyCinderGLDrawing

static MyCinderGLDrawing *_instance = nil;  // <-- important 

+(MyCinderGLDrawing *)instance { 
	// skip everything
	if(_instance) return _instance; 
    
	// Singleton
	@synchronized([MyCinderGLDrawing class]) {
		if(!_instance) {
			_instance = [[self alloc] init];
            //	NSLog(@"Creating MyCinderGLDrawing instance!"); <-- You should see this once only in your program
		}
        
		return _instance;
	}
    
	return nil;
}

/**
 *  The superclass setup method
 */

- (void) setup
{
	[super setup];
	
    _instance = self;
    _ribbonPaint = new RibbonPaint();
    _ribbonPaint->setup();
}



/**
 *  The superclass draw loop method
 */

- (void) draw {
   _ribbonPaint->update();
   _ribbonPaint->draw();
}




/**
 *  Custom drawing methods
 */

void drawGrid(float size, float step)
{
	for(float i=-size;i<=size;i+=step) {
		gl::drawLine( Vec3f(i, 0.0f, -size), Vec3f(i, 0.0f, size) );
		gl::drawLine( Vec3f(-size, 0.0f, i), Vec3f(size, 0.0f, i) );
	}
}




/**
 *  Cocoa UI methods
 */

- (void) setCubeSize: (int) size
{
	mCubeSize = size;
    ci::app::console() << size << endl;
}



/**
 *  Superclass events
 */

- (void)reshape
{
	[super reshape];
	
//	CameraPersp cam;
//	cam = mMayaCam.getCamera();
//	cam.setAspectRatio( [self getWindowAspectRatio] );
//	mMayaCam.setCurrentCam( cam );
}

- (void)mouseDown:(NSEvent*)theEvent
{
	[super mouseDown:(NSEvent *)theEvent];
	
	NSPoint curPoint = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    curPoint.y = self.frame.size.height - curPoint.y;
    _ribbonPaint->mouseDown( Vec2f(curPoint.x, curPoint.y) );
//	mMayaCam.mouseDown( Vec2i(curPoint.x, curPoint.y) );
	//console() << "MouseDown x : " << curPoint.x << ", y : " << curPoint.y << endl;
}

- (void)mouseDragged:(NSEvent *)theEvent {
	[super mouseDragged:(NSEvent *)theEvent];
	
	NSPoint curPoint = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    curPoint.y = self.frame.size.height - curPoint.y;
    _ribbonPaint->mouseDrag( Vec2f(curPoint.x, curPoint.y) );
}

- (void)mouseUp:(NSEvent *)theEvent {
	[super mouseUp:(NSEvent *)theEvent];
	
	NSPoint curPoint = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    curPoint.y = self.frame.size.height - curPoint.y;
    _ribbonPaint->mouseUp( Vec2f(curPoint.x, curPoint.y) );
}

- (void)mouseMoved:(NSEvent *)theEvent {
	[super mouseMoved:(NSEvent *)theEvent];
	
    NSPoint curPoint = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    curPoint.y = self.frame.size.height - curPoint.y;
//    NSLog(@"Offset %0.0f", offset);
    NSLog(@"Frame: %0.0f, %0.0f | mouse: %0.0f, %0.0f", self.frame.origin.x, 
          self.frame.origin.y, curPoint.x, curPoint.y );
    
    _ribbonPaint->mouseMove( Vec2f(curPoint.x, curPoint.y) );
}

@end
