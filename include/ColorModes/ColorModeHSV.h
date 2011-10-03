/*
 * ColorModeHSV.h
 *
 *  Created on: Sep 30, 2011
 *      Author: mariogonzalez
 */

#ifndef COLORMODEHSV_H_
#define COLORMODEHSV_H_

#include "IColorMode.h"

namespace ColorModes {

	class ColorModeHSV: public IColorMode {
		public:
			ColorModeHSV() {};
			virtual ~ColorModeHSV() {};
			virtual void update() {};
			virtual void exit() {};
			virtual void enter() {
				ci::gl::enableAdditiveBlending();
				ci::gl::clear( getBackgroundColor() );
			}
			virtual void setColor( double inverseI ) const {
				ci::ColorA color( ci::CM_HSV,
								ci::math<float>::clamp(0.28 * ci::math<float>::cos( inverseI * M_PI * 2 ) * 0.83, 0.0f, 1.0),
								ci::math<float>::max( 0.89 + sin( inverseI * M_PI * 2 ) * 0.51, 1.0 ),
								0.05,
								inverseI * getAlpha() );
						ci::gl::color(color);
			}
			virtual ci::Colorf getBackgroundColor() const { return ci::Colorf(0, 0, 0); }
			virtual float getAlpha() const { return 1.0; };

		protected:
			ci::ColorA _color;
	};
};

#endif /* COLORMODEHSV_H_ */
