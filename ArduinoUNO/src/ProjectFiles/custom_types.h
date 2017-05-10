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


#ifndef CUSTOM_TYPES_H_
#define CUSTOM_TYPES_H_

#define ON 1
#define OFF 0

/*Include Arduino headers*/
#include <Arduino.h>

/**
* @brief Implementation of bit field
*
* mplementation of function that handles the initialization of motor control
**/


struct BIT {
	uint8_t  b0     :1;  // bit 0 single bit
	uint8_t  b1     :1;  // bit 1 single bit
	uint8_t  b2		:1;  // bit 2 single bit
	uint8_t  b3		:1;  // bit 3 single bit
	uint8_t  b4		:1;  // bit 4 single bit
	uint8_t  b5		:1;  // bit 5 single bit
	uint8_t  b6		:1;  // bit 6 single bit
	uint8_t  b7		:1;  // bit 7 single bit
};


/**
* @brief Implementation of union bit field
*
* mplementation of function that handles the initialization of motor control
**/

union flags8 {
	uint8_t  byte;
	struct BIT bits;
};



#endif /* CUSTOM_TYPES_H_ */