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
 * @file ProjectMain.cpp
 * @author Adrian
 * @date 26/05/2015
 * @brief File containing functions for IO External
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */

/*Include Header files*/
#include <ProjectMain.h>

/*IO*/
#include "IO_extern.h"

/*applications*/
#include "lights_extern.h"
#include "motors_extern.h"
#include "flasher_extern.h"
#include "brake_extern.h"

/*FOR PWM*/
#include <avr/io.h>
#include <avr/interrupt.h>

/*Include H Files*/
#include "schedulerConfig.h"

/*
* Main code called on reset is in  Arduino.h
*/


#ifdef ENABLE_DEBUG
/*
 * @brief Used to provide debug data through serial port
 *
 * Array of tasks and interval of execution
 */
 uint8_t debugBuffer_au8[255]; 
 uint8_t debugArrIndex_u8 = 0;
#endif


/**
 * @brief Array of tasks and interval of execution
 *
 * Array of tasks and interval of execution
 */
static TaskType_stType tasks_st[] = {
	{ T_INTERVAL_20MS,	task20ms },
	{ T_INTERVAL_40MS,	task40ms },
	{ T_INTERVAL_60MS,	task60ms },
	{ T_INTERVAL_100MS,	task100ms },
	{ T_INTERVAL_1000MS,task1000ms},			
};

/**
 * @brief Implementation of the function that returns a pointer to the tasks array
 *
 * @return A pointer to the array of tasks
 * @see tasks_st[];
 */
TaskType_stType *taskGetConfigPtr(void) {
	return tasks_st;
}

/**
 * @brief Implementation of the function that returns the number of current tasks cheduled to run
 *
 * @return number of tasks
 */
uint8_t getNrTasks(void) {
	return sizeof(tasks_st) / sizeof(*tasks_st);
}


uint8_t stui_TaskIndex;
volatile uint8_t taskTimeCounterFlag_u8;
volatile uint8_t taskTimeCounter_u8;
const uint8_t cui_numberOfTasks = getNrTasks();

static TaskType_stType *taskPtr;



void setup()
{
	taskTimeCounterFlag_u8 = 0;
	taskTimeCounter_u8 = 0;	
	stui_TaskIndex = 0;				
	taskPtr = taskGetConfigPtr();		
	#ifdef ENABLE_DEBUG
		Serial.begin(115200);
		//Serial.println("Serial Debug has started");
	#endif				
	timer0_init();	
	timer1_init();	
	//Application inits:
	motorsInit();
	lightsInit();
	flasherInit();
	brakeInit();
	}



void loop()
{	
	
	
	// if 20ms have passed
	if(taskTimeCounterFlag_u8==1) {
		for(stui_TaskIndex=0; stui_TaskIndex < cui_numberOfTasks; stui_TaskIndex++) {
			if((taskTimeCounter_u8 % taskPtr[stui_TaskIndex].interval_u16) == 0 ) {
			
				if((taskPtr[stui_TaskIndex].ptrFunc) != NULL) {
					(*taskPtr[stui_TaskIndex].ptrFunc)();	
				} else {
					// do nothing
				}
			}
		
		}
		taskTimeCounterFlag_u8 = 0;
	}
}

/**
* @brief Implementation of function that handle the 20ms requests
*
* Implementation of function that handle the 20ms requests
* @return void
* @note Void function with no return.
*/
void task20ms(void) {
	//  20ms  cyclic function of the flasher functionality
	flasherCyclic();
}


/**
* @brief Implementation of function that handle the 40ms requests
*
* Implementation of function that handle the 40ms requests
* @return void
* @note Void function with no return.
*/
void task40ms(void) {
	brakeCyclic();
	lowBeamCyclic();
};

/**
* @brief Implementation of function that handle the 60ms requests
*
* Implementation of function that handle the 60ms requests
* @return void
* @note Void function with no return.
*/
void task60ms(void) {
	
};


/**
* @brief Implementation of function that handle the 100ms requests
*
* Implementation of function that handle the 100ms requests
* @return void
* @note Void function with no return.
*/
void task100ms(void) {
	processSerialDebugData();
};

/**
* @brief Implementation of function that handle the 1000ms requests
*
* Implementation of function that handle the 1000ms requests
* @return void
* @note Void function with no return.
*/
void task1000ms(void) {
//uint8_t index_u8;
//	for(index_u8=0;index_u8<=EN_NUMBER_OF_ELEMENTS_INPUT;index_u8++){
//		AddSerialDebugData( getOutputs((EN_OUTPUT_PINS)index_u8) );
//	}
}

/**
 * @brief Implementation of the function that initialize the timer0 
 * 
 * Implementation of the function that initialize the timer 0 used in ADC conversion
 * @return void
 *  
 */
void timer0_init() 
{
	DDRD=(1<<PORTD6);/**< digital pin6 is an output for lowbeam*/
	TCCR0A=(1<<COM0A1);		/**<Clear OC0A on Compare Match */
	TIMSK0=(1<<TOIE0);		/**<enable interrupt on compare */
	sei();
	TCCR0B=(1<<CS02)|(1<<CS00); /**< sets the prescaler to 1024;*/
}

/**
 * @brief Implementation of the function that initialize the timer1
 * 
 * Implementation of the function that initialize the timer 1 
 * @return void
 *  
 */
void timer1_init() {
	
	// initialize Timer1
	cli();             // disable global interrupts
	TCCR1A = 0;        // set entire TCCR1A register to 0
	TCCR1B = 0;
	
	// initialize counter
	TCNT1 = T_TIMER_START;
	
	// enable Timer1 overflow interrupt:
	TIMSK1 = (1 << TOIE1);
	// set the timer with a prescaller of 256
	TCCR1B |= (1 << CS12);
	// enable global interrupts:
	sei();
}

/**
 * @brief Implementation of the function that handle timer1 overflow ISR
 * 
 * Implementation of the function that handle timer1 overflow ISR
 * @return void
 *  
 */
ISR(TIMER1_OVF_vect) {
	TCNT1 = T_TIMER_START;
	taskTimeCounterFlag_u8 = 1;
	taskTimeCounter_u8++;
}



#ifdef ENABLE_DEBUG
/**
 * @brief Add debug data to buffer that will be sent out through serial port
 * 
 * Implementation of the function that handle timer1 overflow ISR
 * @return 0: not success, 1: success
 *  
 */	
uint8_t AddSerialDebugData(uint8_t Value_lu8)
{
	 if (debugArrIndex_u8<255)
	 {		 
		 debugBuffer_au8[debugArrIndex_u8] = Value_lu8;
		 debugArrIndex_u8++;
		 return 1u;
	 }
	 else
	 {		 
		 //buffer full
		 return 0u;
	 }	
}

/**
 * @brief Function will try to send out debug info through serial port
 * * 
 * @return void
 *  
 */	
void processSerialDebugData()
{
	 uint8_t data_lu8;
	 if (debugArrIndex_u8)
	 {
		 if (Serial.availableForWrite()>=1)
		 {
		
			 data_lu8 = debugBuffer_au8[debugArrIndex_u8];
			 Serial.write(data_lu8);
			 debugArrIndex_u8--;
		 }
		 else
		 {
			  static uint8_t flag=0;
			  flag=1-flag;
			  digitalWrite(6,flag);
			 //wait for a round
		 }		 
	 }
	 else
	 {
		 //nothing to send out		 
	 }
}


#endif