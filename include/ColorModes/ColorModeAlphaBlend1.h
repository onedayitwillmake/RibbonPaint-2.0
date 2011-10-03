/*
 * ColorModeHSV.h
 *
 *  Created on: Sep 30, 2011
 *      Author: mariogonzalez
 */

#ifndef COLORMODEALPHABLEND1_H_H
#define COLORMODEALPHABLEND1_H_H

#include "IColorMode.h"

namespace ColorModes {

	class ColorModeAlphaBlend1: public IColorMode {
		public:
			ColorModeAlphaBlend1() {};
			virtual ~ColorModeAlphaBlend1() {};
			virtual void update() {};
			virtual void exit() {};
			virtual void enter() {
				ci::gl::enableAlphaBlending();
				ci::gl::clear( getBackgroundColor() );
			}
			virtual void setColor( double inverseI ) const {
				float left = 0.4;
				float right = 0.5;
				ci::gl::color( ci::ColorA(1.0 - (left + (inverseI * right)),
								1.0 - (left + (sin(inverseI * M_PI * 2) * right)),
								1.0 - (left + (cos(inverseI * M_PI * 2) * right)),
								inverseI * getAlpha() )	);
			}
			virtual ci::Colorf getBackgroundColor() const { return ci::Colorf(1, 1, 1); }
			virtual float getAlpha() const { return 1.0; };

		protected:
			ci::ColorA _color;
	};
};

#endif /* COLORMODEALPHABLEND1_H_H */
