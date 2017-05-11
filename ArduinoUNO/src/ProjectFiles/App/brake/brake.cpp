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
 * brake.cpp
 *
 * Created: 5/4/2017 3:17:52 PM
 *  Author: octavian.rusu
 */ 
#include "low_beam_extern.h"
#include "custom_types.h"
#include "brake.h"
#include "IO_extern.h"


typedef enum en_brakeLight_states {
	EN_BRAKE_STATE_BRAKING ,				/**< Braking */
	EN_BRAKE_STATE_STOP_LIGHT ,				/**< StopLights */
	EN_BRAKE_STATE_LIGHTS_OFF ,				/**< LightsOff */
	EN_BRAKE_NUMBER_OF_ELEMENTS_STATES ,      /**< Number of states*/
} EN_BRAKE_STATES;

typedef enum en_brake_reqest_states {
	EN_BRAKE_REQ_STATE_BRAKING,					/**< brake req state braking */
	EN_BRAKE_REQ_STATE_STOP_LIGHT,					/**< brake req state stop light */
	EN_BRAKE_REQ_STATE_LIGHTS_OFF ,				/**< lights off req */
	EN_BRAKE_REQ_NUMBER_OF_ELEMENTS_STATES ,      /**< Number of states*/
} EN_BRAKE_REQUEST_STATES;

/**
 * @brief enum of states
 *
 *  enum of states
 */
EN_BRAKE_STATES brakeStates_en;

/**
 * @brief enum of states
 *
 *  enum of states
 */
EN_BRAKE_REQUEST_STATES brakeReqStates_en;

/**
 * @brief union of flags
 *
 *  union of flags
 */
flags8 flags8_brake_u;
#define BRAKE_PEDAL_INPUT flags8_brake_u.bits.b0
#define LIGHT_STATE flags8_brake_u.bits.b1

#define TIME_BRAKE_STUCK_DETECTION (1000u/40u)       /**< 1 sec in 40 ms cyclic task*/

/**
* @brief Init function of the brake functionality
*
*  Longer version of the description of the Init function of the brake functionality
* @return void
* @note Void function with no return.
*/
void brakeInit()
{
	brakeStates_en = EN_BRAKE_STATE_STOP_LIGHT;
	brakeReqStates_en = EN_BRAKE_REQ_STATE_STOP_LIGHT;
}

/**
* @brief Implementation of function that handles the brake control lights
*
* Implementation of function that handles the brake control
* @return void
* @note Void function with no return.
*/
void brakeCyclic()
{
		brakeInputsAQ();
		brakeSM();
		brakeActuator();
}

/**
* @brief Implementation of function that handles the brake input aquisition
*
* Implementation of function that handles the brake control
* @return void
* @note Void function with no return.
*/

void brakeInputsAQ()
{
	uint8_t cntBrakeInputStuckDetection_lu8; 
	
	BRAKE_PEDAL_INPUT = GetInputPin(EN_SID_WIFI_CONTROL_DOWN);
	LIGHT_STATE = getLightsState();
	
	if(BRAKE_PEDAL_INPUT)
	{
		if(cntBrakeInputStuckDetection_lu8>0)
		{
			cntBrakeInputStuckDetection_lu8--;
		}
		else
		{
			//seterror(brake)
		}
	}
	else
	{
		cntBrakeInputStuckDetection_lu8 = TIME_BRAKE_STUCK_DETECTION;
	}
	if(BRAKE_PEDAL_INPUT)  //brake button pressed
	{
		brakeReqStates_en = EN_BRAKE_REQ_STATE_BRAKING;
	}
	else
	{
		if(LIGHT_STATE)   //lights are on
		{
			brakeReqStates_en = EN_BRAKE_REQ_STATE_STOP_LIGHT;
		}
		else                   // lights are off
			brakeReqStates_en = EN_BRAKE_REQ_STATE_LIGHTS_OFF;
	}
}

/**
* @brief Implementation of function that handles the brake state machine
*
* Implementation of function that handles the brake control
* @return void
* @note Void function with no return.
*/
void brakeSM()
{
	switch(brakeStates_en)
	{
		case EN_BRAKE_STATE_BRAKING:
			switch(brakeReqStates_en)
			{
				case EN_BRAKE_REQ_STATE_STOP_LIGHT:
					brakeStates_en = EN_BRAKE_STATE_STOP_LIGHT;
				break;
				case EN_BRAKE_REQ_STATE_LIGHTS_OFF:
					brakeStates_en = EN_BRAKE_STATE_LIGHTS_OFF;
				default: //keep last value
				break;
				
			}
		break;
		case EN_BRAKE_STATE_STOP_LIGHT:
			switch(brakeReqStates_en)
			{
				case EN_BRAKE_REQ_STATE_BRAKING:
					brakeStates_en = EN_BRAKE_STATE_BRAKING;
				break;
				case EN_BRAKE_REQ_STATE_LIGHTS_OFF:
					brakeStates_en = EN_BRAKE_STATE_LIGHTS_OFF;
				break;
				default: //keep last value
				break;
			}
		break;
		case EN_BRAKE_STATE_LIGHTS_OFF:
			switch(brakeReqStates_en)
			{
				case EN_BRAKE_REQ_STATE_BRAKING:
					brakeStates_en = EN_BRAKE_STATE_BRAKING;
				break;
				case EN_BRAKE_REQ_STATE_STOP_LIGHT:
					brakeStates_en = EN_BRAKE_STATE_STOP_LIGHT;
				break;
				default: //keep last value
				break;
			}
		break;
		default:
			brakeStates_en = EN_BRAKE_STATE_STOP_LIGHT;
		break;
	}
}

/**
* @brief Implementation of function that handles the brake actuator
*
* Implementation of function that handles the brake actuator
* @return void
* @note Void function with no return.
*/
void brakeActuator()
{
	if(brakeStates_en == EN_BRAKE_STATE_BRAKING)
	{
		setOutputPin(EN_SODPWM_BRAKE_LIGHT, 100);
	}
	
	if(brakeStates_en == EN_BRAKE_STATE_STOP_LIGHT)
	{
		setOutputPin(EN_SODPWM_BRAKE_LIGHT, 50);
	}
	
	if(brakeStates_en == EN_BRAKE_STATE_LIGHTS_OFF)
	{
		setOutputPin(EN_SODPWM_BRAKE_LIGHT, 0);
	}
}

