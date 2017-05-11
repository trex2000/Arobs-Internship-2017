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
/*
 * low_beam.h
 *
 * Created: 04/05/2017 15:14:47
 *  Author: raul.butunoi
 */ 


#ifndef LOW_BEAM_H_
#define LOW_BEAM_H_

/**
* @brief Implementation of function that handles the initialization of lowbeam control
*
* mplementation of function that handles the initialization of lowbeam control
* @return void
* @note Void function with no return.
*/
void lowBeamInit();

/**
* @brief Implementation of function that handles the lowbeam control
*
* Implementation of function that handles the lowbeam control
* @return void
* @note Void function with no return.
*/
void lowBeamCyclic();


/**
* @brief Implementation of function that handles the lowbeam control
*
* Implementation of function that handles the lowbeam control
* @return void
* @note Void function with no return.
*/

void lowBeamInputsAQ();

/**
* @brief Implementation of function that handles the lowbeam control
*
* Implementation of function that handles the lowbeam control
* @return void
* @note Void function with no return.
*/

void lowBeamSM();

/**
* @brief Implementation of lowbeam actuator
*
* Implementation of function that handles the lowbeam actuator
* @return void
* @note Void function with no return.
*/
void lowBeamActuator();



#endif /* LOW_BEAM_H_ */