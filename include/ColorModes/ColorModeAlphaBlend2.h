/*
 * ColorModeHSV.h
 *
 *  Created on: Sep 30, 2011
 *      Author: mariogonzalez
 */

#ifndef COLORMODEALPHABLEND2_H_
#define COLORMODEALPHABLEND2_H_

#include "IColorMode.h"

namespace ColorModes {

	class ColorModeAlphaBlend2: public IColorMode {
		public:
			ColorModeAlphaBlend2() {};
			virtual ~ColorModeAlphaBlend2() {};
			virtual void update() {};
			virtual void exit() {};
			virtual void enter() {
				ci::gl::enableAlphaBlending();
				ci::gl::clear( getBackgroundColor() );
			}
			virtual void setColor( double inverseI ) const {
				ci::gl::color( ci::ColorA(0.83 + (inverseI * 0.4),
						  0.4 + (cos(inverseI * M_PI * 2) * 0.44),
						  (0.37 + (sin(inverseI * M_PI * 2) * 0.4)),
						  inverseI * getAlpha() ) );
			}
			virtual ci::Colorf getBackgroundColor() const { return ci::Colorf(1, 1, 1); }
			virtual float getAlpha() const { return 1.0; };

		protected:
			ci::ColorA _color;
	};
};

#endif /* COLORMODEALPHABLEND2_H_ */
