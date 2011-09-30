//
//  MyCinderGLDrawing.h
//  CCGLBasic example
//
//  Created by Matthieu Savary on 03/03/11.
//  Copyright (c) 2011 SMALLAB.ORG. All rights reserved.
//
//  More info on the CCGL project >> http://www.smallab.org/code/ccgl/
//  License & disclaimer >> see license.txt file included in the distribution package
//

#include "CCGLView.h"

#include "cinder/Camera.h"
#include "cinder/MayaCamUI.h"
#include "RibbonPaint.h"

#import <AppKit/AppKit.h>


@interface MyCinderGLDrawing : CCGLView
{
    RibbonPaint* _ribbonPaint;
	int mCubeSize;
}

/**
 *  Custom drawing methods
 */

void drawGrid(float size, float step);

/**
 *  Cocoa UI methods
 */

- (void) setCubeSize: (int) bits;

+(MyCinderGLDrawing*) instance;
@end
