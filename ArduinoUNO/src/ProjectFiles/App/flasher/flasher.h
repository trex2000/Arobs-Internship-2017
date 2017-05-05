/****************************************************************************
 * Copyright (C) 2015														*
 *                                                                          *
 * This file is part of RC CAR                                              *
 *                                                                          *
 *   Box is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Box is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/
#pragma once

#ifndef FLASHER_H_
#define FLASHER_H_

/**
* @brief Init function of the flasher functionality
*
*  Longer version of the description of the Init function of the flasher functionality
* @return void
* @note Void function with no return.
*/
 void flasherInit();

/**
* @brief Cyclic function of the flasher functionality
*
*  Longer version of the description of the Cyclic function of the flasher functionality
* @return void
* @note Void function with no return.
*/
 void flasherCyclic();


/**
* @brief Implementation of function that handles the flasher input aquisition
*
* Implementation of function that handles the flasher control
* @return void
* @note Void function with no return.
*/

void flasherInputsAQ();

/**
* @brief Implementation of function that handles the flasher state machine
*
* Implementation of function that handles the flasher control
* @return void
* @note Void function with no return.
*/
void flasherSM();

/**
* @brief Implementation of function that handles the flasher actuator
*
* Implementation of function that handles the flasher actuator
* @return void
* @note Void function with no return.
*/
void flasherActuator();


#endif /* FLASHER_H_ */