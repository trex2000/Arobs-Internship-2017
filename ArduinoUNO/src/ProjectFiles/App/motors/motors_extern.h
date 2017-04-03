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

/**
 * @file motors_extern.h
 * @author Barney
 * @date 16 Jul 2015
 * @brief File containing functions for Motor control
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */

#pragma once

#ifndef MOTORS_EXTERN_H_
#define MOTORS_EXTERN_H_

	
/**
* @brief Implementation of function that handles the initialization of motor control
*
* mplementation of function that handles the initialization of motor control
* @return void
* @note Void function with no return.
*/
void motorsInit();

/**
* @brief Implementation of function that handles the motor control
*
* Implementation of function that handles the motor control
* @return void
* @note Void function with no return.
*/
extern void motorsCyclic();



#endif /* MOTORS_EXTERN_H_ */