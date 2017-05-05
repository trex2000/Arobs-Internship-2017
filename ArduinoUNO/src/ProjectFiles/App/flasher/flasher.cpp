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

/**
 * @file lights.c
 * @author Alex
 * @date 10 Jul 2015
 * @brief File containing functions for IO 
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */

#include "custom_types.h"
#include "flasher.h"
#include "IO_extern.h"
/**
 * @brief Enumeration of movement states
 *
 * Enumeration of movement states.
 */
typedef enum en_flasher_states {
	EN_FLA_STATE_OFF,				/**< flasher Off */
	EN_FLA_STATE_LEFT,				/**< flashing left side */
	EN_FLA_STATE_RIGHT,			/**< flashing right side*/
	EN_FLA_STATE_HAZARD,			/**< hazard  flashing*/
	EN_FLA_NUMBER_OF_ELEMENTS_STATES ,      /**< Number of states*/
} EN_FLASHER_STATES;

typedef enum en_flasher_reqest_states {
	EN_FLA_REQ_STATE_OFF,					/**< flasher req state Off */
	EN_FLA_REQ_STATE_LEFT,					/**< flashing req state left side */
	EN_FLA_REQ_STATE_RIGHT,					/**< flashing req right side*/
	EN_FLA_REQ_STATE_HAZARD,				/**< req hazard  flashing*/
	EN_FLA_REQ_STATE_ERROR,					/**< Error state*/
	EN_FLA_REQ_NUMBER_OF_ELEMENTS_STATES ,      /**< Number of states*/
} EN_FLASHER_REQUEST_STATES;


/**
 * @brief enum of states
 *
 *  enum of states
 */
EN_FLASHER_STATES flasherStates_en;

/**
 * @brief enum of states
 *
 *  enum of states
 */
EN_FLASHER_REQUEST_STATES flasherReqStates_en;


/**
 * @brief union of flags
 *
 *  union of flags
 */
flags8 flags8_flasher_u;


#define EN_SID_FLA_LEFT 0
#define EN_SID_FLA_RIGHT 0
#define EN_SID_HAZARD_BUTTON 0

/**
* @brief Init function of the flasher functionality
*
*  Longer version of the description of the Init function of the flasher functionality
* @return void
* @note Void function with no return.
*/
void flasherInit()
{
	flasherStates_en = EN_FLA_STATE_OFF;
	flasherReqStates_en = EN_FLA_REQ_STATE_OFF;
}

/**
* @brief Cyclic function of the flasher functionality
*
*  Longer version of the description of the Cyclic function of the flasher functionality
* @return void
* @note Void function with no return.
*/
void flasherCyclic()
{
	flasherInputsAQ();
	flasherSM();
	flasherActuator();
}


/**
* @brief Implementation of function that handles the flasher input aquisition
*
* Implementation of function that handles the flasher control
* @return void
* @note Void function with no return.
*/

void flasherInputsAQ()
{
	
	if (GetInputPin((EN_INPUT_PINS)EN_SID_HAZARD_BUTTON))
	{
		flasherReqStates_en = EN_FLA_REQ_STATE_HAZARD;
	}
	else
	{
		if (
			GetInputPin((EN_INPUT_PINS)EN_SID_FLA_LEFT) && GetInputPin((EN_INPUT_PINS)EN_SID_FLA_RIGHT)
			)
		{
			flasherReqStates_en = EN_FLA_REQ_STATE_ERROR;	
		}
		else
		{
			if (GetInputPin((EN_INPUT_PINS)EN_SID_FLA_LEFT))
			{
				flasherReqStates_en = EN_FLA_REQ_STATE_LEFT;
			}
			else
			{
				if (GetInputPin((EN_INPUT_PINS)EN_SID_FLA_RIGHT))
				{
					flasherReqStates_en = EN_FLA_REQ_STATE_RIGHT;
				}
				else
				{
					flasherReqStates_en = EN_FLA_REQ_STATE_OFF;
				}
			}
		}
	}

}


/**
* @brief Implementation of function that handles the flasher state machine
*
* Implementation of function that handles the flasher control
* @return void
* @note Void function with no return.
*/
void flasherSM()
{
	switch(flasherStates_en)
	{
		case EN_FLA_STATE_OFF:
				switch(flasherReqStates_en)
				{
					case EN_FLA_REQ_STATE_LEFT:
							flasherStates_en = EN_FLA_STATE_LEFT;
					break;
					case EN_FLA_REQ_STATE_RIGHT:
							flasherStates_en = EN_FLA_STATE_RIGHT;
					break;
					case	EN_FLA_REQ_STATE_HAZARD:
					case	EN_FLA_REQ_STATE_ERROR:
							flasherStates_en = EN_FLA_STATE_HAZARD;
					break;
					default: //keep last value
					break;
				}
		break;
		case EN_FLA_STATE_LEFT:
				switch(flasherReqStates_en)
				{
					case EN_FLA_REQ_STATE_OFF:
						flasherStates_en = EN_FLA_STATE_OFF;
					break;
					case EN_FLA_REQ_STATE_RIGHT:
						flasherStates_en = EN_FLA_STATE_RIGHT;
					break;
					case	EN_FLA_REQ_STATE_HAZARD:
					case	EN_FLA_REQ_STATE_ERROR:
						flasherStates_en = EN_FLA_STATE_HAZARD;
					break;
					default: //keep last value
					break;
				}
		break;
		case EN_FLA_STATE_RIGHT:
				switch(flasherReqStates_en)
				{
					case EN_FLA_REQ_STATE_OFF:
						flasherStates_en = EN_FLA_STATE_OFF;
					break;
					case EN_FLA_REQ_STATE_RIGHT:
						flasherStates_en = EN_FLA_STATE_RIGHT;
					break;
					case	EN_FLA_REQ_STATE_HAZARD:
					case	EN_FLA_REQ_STATE_ERROR:
						flasherStates_en = EN_FLA_STATE_HAZARD;
					break;
					default: //keep last value
					break;
				}
		break;
		case EN_FLA_STATE_HAZARD:
				switch(flasherReqStates_en)
				{
					case EN_FLA_REQ_STATE_OFF:
						flasherStates_en = EN_FLA_STATE_OFF;
					break;
					case EN_FLA_REQ_STATE_RIGHT:
						flasherStates_en = EN_FLA_STATE_RIGHT;
					break;
					case EN_FLA_REQ_STATE_LEFT:
						flasherStates_en = EN_FLA_STATE_LEFT;
					break;
					default: //keep last value
					break;		
				}
		break;
		default:
			flasherStates_en = EN_FLA_STATE_HAZARD;	
		break;
	}
}

/**
* @brief Implementation of function that handles the flasher actuator
*
* Implementation of function that handles the flasher actuator
* @return void
* @note Void function with no return.
*/
void flasherActuator()
{
	
}