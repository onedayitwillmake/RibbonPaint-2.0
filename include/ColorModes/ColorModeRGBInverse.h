/*
 * ColorModeHSV.h
 *
 *  Created on: Sep 30, 2011
 *      Author: mariogonzalez
 */

#ifndef COLORMODESRGBINVERSE_H_
#define COLORMODESRGBINVERSE_H_

#include "IColorMode.h"

namespace ColorModes {

	class ColorModeRGB: public IColorMode {
		public:
			ColorModeRGB() {};
			virtual ~ColorModeRGB() {};
			virtual void update() {};
			virtual void exit() {};
			virtual void enter() {
				ci::gl::enableAdditiveBlending();
				ci::gl::clear( getBackgroundColor() );
			}
			virtual void setColor( double inverseI ) const {
				float left = 0.35;
				float right = 0.45;
				ci::gl::color( ci::ColorA(0.9 - (left + (inverseI * right)),
						  0.9 - (left + ( ci::math<float>::sin(inverseI * M_PI * 2) * right) ),
						  0.9 - (left + ( ci::math<float>::cos(inverseI * M_PI * 2) * right) ),
						  inverseI * getAlpha()*0.8) );
			}
			virtual ci::Colorf getBackgroundColor() const { return ci::Colorf(0, 0, 0); }
			virtual float getAlpha() const { return 1.0; };

		protected:
			ci::ColorA _color;
	};
};

#endif /* COLORMODESRGBINVERSE_H_ */
