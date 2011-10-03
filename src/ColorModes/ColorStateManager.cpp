/*
 * ColorStateManager.cpp
 *
 *  Created on: Sep 30, 2011
 *      Author: mariogonzalez
 */

#include "ColorStateManager.h"
#include <iostream>

namespace ColorModes {
	ColorStateManager::ColorStateManager() {
		currentState = NULL;
		previousState = NULL;
		nextState = NULL;
	}

	ColorStateManager::~ColorStateManager() {
		delete currentState;
		delete previousState;
		delete nextState;

		std::cout << "ColorStateManager destructor!" << std::endl;
	}

	void ColorStateManager::setInitialState( IColorMode* aState ) {
		currentState = aState;
		currentState->enter();
	}

	void ColorStateManager::changeState( IColorMode* aState ) {
//		if(aState != previousState)
//			delete previousState;

		currentState->exit();
		previousState = currentState;

		currentState = aState;
		currentState->enter();
	}

	void ColorStateManager::gotoPreviousState() {
		changeState( previousState );
	}

	void ColorStateManager::gotoNextState()  {
		changeState( nextState );
	}

	void ColorStateManager::update() {
//		if( currentState ) {
//			currentState->update();
//		}
	}

	void ColorStateManager::draw() {
//		if( currentState ) {
//			currentState->draw();
//		}
	}
}
