/*
 * ColorStateManager.h
 *
 *  Created on: Sep 30, 2011
 *      Author: mariogonzalez
 */

#ifndef COLORSTATEMANAGER_H_
#define COLORSTATEMANAGER_H_
#include "IColorMode.h"

namespace ColorModes {
	class ColorStateManager {
		public:
			ColorStateManager();
			virtual ~ColorStateManager();

			void setInitialState( IColorMode* aState );
			void changeState( IColorMode* aState );
			void gotoPreviousState();
			void gotoNextState();

			void update();
			void draw();

			const IColorMode* getColorModel() { return currentState; };
		private:
			IColorMode* currentState;
			IColorMode* previousState;
			IColorMode* nextState;
	};
}
#endif /* COLORSTATEMANAGER_H_ */
