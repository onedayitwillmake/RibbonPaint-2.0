/*
 * ColorModeHSV.h
 *
 *  Created on: Sep 30, 2011
 *      Author: mariogonzalez
 */

#ifndef COLORMODEALPHABLEND3_H_
#define COLORMODEALPHABLEND3_H_

#include "IColorMode.h"

namespace ColorModes {

	class ColorModeAlphaBlend3: public IColorMode {
		public:
			ColorModeAlphaBlend3() {};
			virtual ~ColorModeAlphaBlend3() {};
			virtual void update() {};
			virtual void exit() {};
			virtual void enter() {
				ci::gl::enableAlphaBlending();
				ci::gl::clear( getBackgroundColor() );
			}
			virtual void setColor( double inverseI ) const {
				ci::gl::color( ci::ColorA( (0.4 + (sin(inverseI * M_PI * 2) * 0.32)),
						  (0.23 + (cos(inverseI * M_PI * 2) * 0.25)),
						  (0.5 + (inverseI * 0.21)),
						  inverseI * getAlpha() ) );
			}
			virtual ci::Colorf getBackgroundColor() const { return ci::Colorf(1, 1, 1); }
			virtual float getAlpha() const { return 1.0; };

		protected:
			ci::ColorA _color;
	};
};

#endif /* COLORMODEALPHABLEND3_H_ */
