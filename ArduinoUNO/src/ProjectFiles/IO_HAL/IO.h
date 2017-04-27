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
 * @file IO.h
 * @author Adrian
 * @date 10 Jul 2015
 * @brief File containing functions for IO External
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */
//#pragma once

#ifndef _IO_H_
#define _IO_H_

#include "Arduino.h"

/**
 * @brief Enumeration of logical inputs
 *
 * Enumeration of logical inputs.
 */
typedef enum en_input_pins {
	EN_SIA_LIGHTSENSOR ,				/**< Lightsensor analogic input */
	EN_SID_WIFI_CONTROL_UP ,			/**< WifiControl Up. */
	EN_SID_WIFI_CONTROL_DOWN ,          /**< WifiControl Down*/
	EN_SID_WIFI_CONTROL_RIGHT ,         /**< WifiControl Right*/
	EN_SID_WIFI_CONTROL_LEFT ,          /**< WifiControl Left */
	EN_NUMBER_OF_ELEMENTS_INPUT ,       /**< Number of input pins*/
} EN_INPUT_PINS;

/**
 * @brief Enumeration of logical outputs
 *
 * Enumeration of logical outputs.
 */
typedef enum en_output_pins {
	EN_SOD_MOTOR12_0,					/**< Motor 12 digital output 1 */
	EN_SOD_MOTOR12_1,				    /**< Motor 12 digital output 2 */
	EN_SOD_MOTOR12_2,				    /**< Motor 12 digital output 3 */
	EN_SOD_MOTOR12_3,					/**< Motor 12 digital output 4 */
	EN_SODPWM_ENABLE_MOTOR1,			/**< Digital out PWM on  Motor1 */
	EN_SODPWM_ENABLE_MOTOR2,			/**< Digital out PWM on  Motor2 */
	EN_SOD_LEFT_FLASHER,				/**< Digital out for Left Flasher */
	EN_SOD_RIGHT_FLASHER,				/**< Digital out for Right Flasher */
	EN_SOD_LOW_BEAM,					/**< Digital out for Low Beam */
	EN_NUMBER_OF_ELEMENTS_OUTPUTS       /**< Number of output pins  */
}EN_OUTPUT_PINS;





/**
 * @brief Macro for testing if a bit is set
 *
 * Macro for testing if a bit is set
 */
#define CHECK_BIT(var,pos) ((var) & (1<<(pos))) 

/**
 * @brief Macro for max PWM value
 *
 * Macro for max PWM value
 */
#define MAX_PWM_VALUE_REG 256
/**
 * @brief Defines maximum number of analog channels
 *
 * Defines maximum number of analog channels
 */
#define MAX_ADC_CHANNELS 6u 

/**
 * @brief Macro implementation for starting the ADC conversion
 *
 * Macro implementation for starting the ADC conversion
 * @return void
 */
#define START_CONVERSION() ADCSRA|=(1<<ADSC)  /**< sets the bit to start the conversion */



/**
 * @brief maximum value for PWM
 *
 * maximum value for PWM
 */
#define MAX_PWM_VALUE  100u

/**
 * @brief maximum value for digital out
 *
 * maximum value for digital out
 */
#define MAX_DIGITAL_VALUE 1u


/**
 * @brief Enumeration of Ports
 *
 * Enumeration of Ports
 */
typedef enum en_port_enums
{
	EN_PORT_B,			/**< Port B  */
	EN_PORT_C,			/**< Port C  */
	EN_PORT_D			/**< Port D  */
}EN_PORT_ENUMS;


/**
 * @brief Defines type of physical port
 *
 * Defines type of physical port
 */
typedef enum port_type_enum
{
	EN_PORT_DI,				/**< Digital Input port */
	EN_PORT_DO,				/**< Digital Output port */
	EN_PORT_AI,				/**< Analog Input port */
	EN_PORT_DOPWM,			/**< Digital PWM Output port */
	EN_PORT_LAST_ELEMENT	/**< Number of port types */
} PORT_TYPES_EN;

/**
 * @brief Defines the states for ADC conversion
 *
 * Defines the states for ADC conversion
 */
typedef enum en_conversion_state{
	EN_CONVERSION_IN_PROGRESS,		/**< Current conversion in progress  */
	EN_CONVERSION_IDLE				/**< No conversion in progress */
} EN_CONVERSION_STATE;

/**
 * @brief New datatype used in table which connects Logical Input Definitions to Physical Input Def
 *
 * New datatype used in table which connects Logical Input Definitions to Physical Input Def
 */
typedef struct port_types_struct
{
	uint8_t portVal_u8;				/**< Bit position of port */
	EN_PORT_ENUMS  portName_en;		/**< Selection of the port */
	PORT_TYPES_EN portType_en;		/**< Type of the port ( Digital, Analog..) */
} PORT_TYPES_ST;




/**
 * @brief Function definition for processing input buffer
 *
 * Function implementation for processing input buffer.
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void processInputBuffer();
void processAnalogInput(EN_INPUT_PINS bufferIndex_len);
void processDigitalInput(EN_INPUT_PINS bufferIndex_len);

/**
 * @brief Function definition for processing output buffer
 *
 * Function implementation for processing output buffer.
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void processOutputBuffer();

/**
 * @brief Function definition for get value
 *
 * Function definition for set output pin
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
int getValue(uint8_t pin);


/**
 * @brief Function definition for processing Digital output
 *
 * Function definition for set output pin
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void processDigitalOutput(EN_OUTPUT_PINS bufferIndex_len);

/**
 * @brief Function definition for processDigitalOutputPWM
 *
 * Function definition for set output pin
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void processDigitalOutputPWM(EN_OUTPUT_PINS bufferIndex_len);


/**
 * @brief Function implementation for analog input from lightsensor
 *
 * Function implementation for analog input from lightsensor
 * @return void
 */
//void setupADC();


/**
 * @brief Function processes ADC conversion
 *
 * Function processes ADC conversion
 * @return void
 */
void processADCconversion();

void initIO();

#endif
