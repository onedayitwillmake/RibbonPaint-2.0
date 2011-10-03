/*
 * ColorModeHSV.h
 *
 *  Created on: Sep 30, 2011
 *      Author: mariogonzalez
 */

#ifndef COLORMODESINVERSE_H
#define COLORMODESINVERSE_H

#include "IColorMode.h"

namespace ColorModes {

	class ColorModeGrayscale: public IColorMode {
		public:
			ColorModeGrayscale() {};
			virtual ~ColorModeGrayscale() {};
			virtual void update() {};
			virtual void exit() {};
			virtual void enter() {
				ci::gl::enableAlphaBlending();
				ci::gl::clear( getBackgroundColor() );
			}
			virtual void setColor( double inverseI ) const {
				ci::gl::color( ci::ColorA( 0.25, 0.25, 0.25, inverseI * getAlpha() * 0.5) );
			}
			virtual ci::Colorf getBackgroundColor() const { return ci::Colorf(1, 1, 1); }
			virtual float getAlpha() const { return 1.0; };

		protected:
			ci::ColorA _color;
	};
};

#endif /* COLORMODESINVERSE_H */
