/*
 * ColorModeHSV.h
 *
 *  Created on: Sep 30, 2011
 *      Author: mariogonzalez
 */

#ifndef COLORMODESRGB_H_
#define COLORMODESRGB_H_

#include "IColorMode.h"

namespace ColorModes {

	class ColorModeRGBInverse: public IColorMode {
		public:
			ColorModeRGBInverse() {};
			virtual ~ColorModeRGBInverse() {};
			virtual void update() {};
			virtual void exit() {};
			virtual void enter() {
				ci::gl::enableAdditiveBlending();
				ci::gl::clear( getBackgroundColor() );
			}
			virtual void setColor( double inverseI ) const {
				ci::gl::color( ci::ColorA( (0.3 + (inverseI * 0.25)),
						  (0.3 + (cos(inverseI * M_PI * 2) * 0.25)),
						  (0.3 + (sin(inverseI * M_PI * 2) * 0.25)),
						  inverseI * getAlpha() ) );
			}
			virtual ci::Colorf getBackgroundColor() const { return ci::Colorf(0, 0, 0); }
			virtual float getAlpha() const { return 1.0; };

		protected:
			ci::ColorA _color;
	};
};

#endif /* COLORMODEHSV_H_ */
