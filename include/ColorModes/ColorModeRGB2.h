/*
 * ColorModeHSV.h
 *
 *  Created on: Sep 30, 2011
 *      Author: mariogonzalez
 */

#ifndef COLORMODESRGB2_H_
#define COLORMODESRGB2_H_

#include "IColorMode.h"

namespace ColorModes {

	class ColorModeRGB2: public IColorMode {
		public:
			ColorModeRGB2() {};
			virtual ~ColorModeRGB2() {};
			virtual void update() {};
			virtual void exit() {};
			virtual void enter() {
				ci::gl::enableAdditiveBlending();
				ci::gl::clear( getBackgroundColor() );
			}
			virtual void setColor( double inverseI ) const {
				ci::gl::color( ci::ColorA(0.0 + inverseI * 0.25,
						  0.0 + cos(inverseI * M_PI * 2) * 0.1,
						  0.0,
						  inverseI * getAlpha() ) );
			}
			virtual ci::Colorf getBackgroundColor() const { return ci::Colorf(0, 0, 0); }
			virtual float getAlpha() const { return 1.0; };

		protected:
			ci::ColorA _color;
	};
};

#endif /* COLORMODESRGB2_H_ */
