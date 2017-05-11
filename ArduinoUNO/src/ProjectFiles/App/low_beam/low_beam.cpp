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

/*
 * low_beam.cpp
 *
 * Created: 04/05/2017 15:12:34
 *  Author: raul.butunoi
 */ 
#include "custom_types.h"
#include "low_beam.h"
#include "IO_extern.h"

/**
* @brief Implementation of function that handles the initialization of lowbeam control
*
* mplementation of function that handles the initialization of lowbeam control
* @return void
* @note Void function with no return.
*/


/**
 * @brief Enumeration of movement states
 *
 * Enumeration of movement states.
 */
typedef enum en_lb_states {
	EN_LB_STATE_ON ,				/**< Lights on */
	EN_LB_STATE_OFF,				/**< Lights off */
	EN_LB_NUMBER_OF_ELEMENTS_STATES ,      /**< Number of states*/
} EN_LB_STATES;

typedef enum en_lb_reqest_states {
	EN_LB_REQ_STATE_ON,					/**< lowBeam req state On */
	EN_LB_REQ_STATE_OFF,					/**< lowBeam req state Off */
	EN_LB_REQ_NUMBER_OF_ELEMENTS_STATES ,      /**< Number of states*/
} EN_LB_REQUEST_STATES;

typedef enum en_lb_button_states {
	EN_LB_BUTTON_STATE_ON ,				/**< Lights on */
	EN_LB_BUTTON_STATE_OFF,				/**< Lights off */
	EN_LB_BUTTON_STATE_AUTO ,				/**< Lights auto */
	EN_LB_BUTTON_NUMBER_OF_ELEMENTS_STATES ,      /**< Number of states*/
} EN_LB_BUTTON_STATES;
/**
 * @brief enum of states
 *
 *  enum of states
 */
EN_LB_STATES lbStates_en;

/**
 * @brief enum of states
 *
 *  enum of states
 */
EN_LB_BUTTON_STATES lbButtonStates_en;

/**
 * @brief enum of states
 *
 *  enum of states
 */
EN_LB_REQUEST_STATES lbReqStates_en;


/**
 * @brief union of flags
 *
 *  union of flags
 */
flags8 flags8_lb_u;





/**
* @brief Init function of the lowbeam functionality
*
*  Longer version of the description of the Init function of the lowbeam functionality
* @return void
* @note Void function with no return.
*/

void lowBeamInit()
{
	lbStates_en = EN_LB_STATE_OFF;
	lbReqStates_en = EN_LB_REQ_STATE_OFF;
}

/**
* @brief Cyclic function of the lowbeam functionality
*
*  Longer version of the description of the Cyclic function of the lowbeam functionality
* @return void
* @note Void function with no return.
*/
void lowBeamCyclic()
{
	lowBeamInputsAQ();
	lowBeamSM();
	lowBeamActuator();
}


/**
* @brief Implementation of function that handles the lowbeam input aquisition
*
* Implementation of function that handles the lowbeam control
* @return void
* @note Void function with no return.
*/

void lowBeamInputsAQ()
{
	
	if (GetInputPin(EN_SIA_LIGHTSENSOR))
	{
		lbReqStates_en = EN_LB_REQ_STATE_ON;
	}
		else
		{

				lbReqStates_en = EN_LB_REQ_STATE_OFF;
		}
	
}

/**
* @brief Implementation of function that handles the lowbeam control
*
* Implementation of function that handles the lowbeam control
* @return void
* @note Void function with no return.
*/

void lowBeamSM()
{
	switch(lbButtonStates_en)
	{
		case EN_LB_BUTTON_STATE_ON:
		lbStates_en=EN_LB_STATE_ON;
		break;
		case EN_LB_BUTTON_STATE_OFF:
		lbStates_en=EN_LB_STATE_OFF;
		break;
		case EN_LB_BUTTON_STATE_AUTO:
			switch(lbReqStates_en)
			{
				case EN_LB_REQ_STATE_ON:
				lbStates_en = EN_LB_STATE_ON;
				break;
				case EN_LB_REQ_STATE_OFF:
				lbStates_en = EN_LB_STATE_OFF ;
				break;
				default: //keep last value
				break;
			}
		break;
		default:
		lbStates_en = EN_LB_STATE_ON;
		break;
	}
	
		
}

/**
* @brief Implementation of lowbeam actuator
*
* Implementation of function that handles the lowbeam actuator
* @return void
* @note Void function with no return.
*/
void lowBeamActuator()
{
	if(lbStates_en==EN_LB_STATE_ON)
	{
		setOutputPin(EN_SOD_LOW_BEAM, 1);
	}
	if(lbStates_en==EN_LB_STATE_OFF)
	{
		setOutputPin(EN_SOD_LOW_BEAM, 0);
	}
}

int getLightsState()
{
	if (GetInputPin(EN_SIA_LIGHTSENSOR))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}