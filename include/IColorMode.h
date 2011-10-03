/*
 * IColorMode.h
 *
 *  Created on: Sep 30, 2011
 *      Author: mariogonzalez
 */

#ifndef ICOLORMODE_H_
#define ICOLORMODE_H_


#include "Cinder/Color.h"
#include "cinder/CinderMath.h"
#include "cinder/gl/gl.h"

namespace ColorModes {
	class IColorMode {
		public:
			virtual ~IColorMode() {};
			virtual void enter() = 0;
			virtual void update() = 0;
			virtual void exit() = 0;

			virtual void setColor( double inverseI ) const = 0;
			virtual ci::Colorf getBackgroundColor() const = 0;
			virtual float getAlpha() const = 0;

		protected:
			ci::ColorA	_color;
	};
}
#endif /* ICOLORMODE_H_ */
