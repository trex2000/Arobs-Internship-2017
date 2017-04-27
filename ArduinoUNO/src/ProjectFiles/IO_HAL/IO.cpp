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
 * @file IO.c
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

#include <avr/io.h>
#include <Arduino.h>
#include "IO.h"


#define CHECK_BIT(var,pos) ((var) & (1<<(pos))) //macro care verifica o pozitie din registru daca e pe 1 logic
#define MAX_PWM_VALUE_REG 256



/**
 * @brief buffer holds the value of the inputs.
 *
 * Detailed buffer holds the value of the inputs.
 */
uint16_t inputBuffer_u16[EN_NUMBER_OF_ELEMENTS_INPUT];

/**
 * @brief array holds the results of ADC conversion
 *
 * array holds the results of ADC conversion
 */

uint16_t adc_Result_u16[MAX_ADC_CHANNELS];

/**
 * @brief buffer holds the value of the outputs.
 *
 * Detailed buffer holds the value of the outputs.
 */
uint8_t outputBuffer_u8[EN_NUMBER_OF_ELEMENTS_OUTPUTS];


/**
 * @brief New datatype used in table which connects Logical Outputs Definitions to Physical Outputs Def
 *
 * New datatype used in table which connects Logical Outputs Definitions to Physical Outputs Def
 */
PORT_TYPES_ST const matchingTableOutputPins_acst[EN_NUMBER_OF_ELEMENTS_OUTPUTS] = {
	{PORTB2, EN_PORT_B, EN_PORT_DO},     /**<SOD_Motor12_0 */
	{PORTB1, EN_PORT_B, EN_PORT_DO},	 /**<SOD_Motor12_1 */
	{PORTD5, EN_PORT_D, EN_PORT_DO},     /**<SOD_Motor12_2 */
	{PORTD4, EN_PORT_D, EN_PORT_DO},     /**<SOD_Motor12_3 */
	{PORTB3, EN_PORT_B, EN_PORT_DOPWM},  /**<SODPWM_EnableMotor1 */
	{PORTD3, EN_PORT_D, EN_PORT_DOPWM},  /**<ODPWM_EnableMotor2 */
	{PORTC2, EN_PORT_C, EN_PORT_DO},     /**<SOD_LeftFlasher */
	{PORTC1, EN_PORT_C, EN_PORT_DO},     /**<SOD_RightFlasher */
	{PORTD6, EN_PORT_D, EN_PORT_DO}      /**<SOD_LowBeam */
};
/**
 * @brief New datatype used in table which connects Logical Input Definitions to Physical Input Def
 *
 * New datatype used in table which connects Logical Input Definitions to Physical Input Def
 */
PORT_TYPES_ST const matchingTableInputPins_acst[EN_NUMBER_OF_ELEMENTS_INPUT] = {
	{ADC0D,  EN_PORT_C, EN_PORT_AI},     /**< EN_SIA_LIGHTSENSOR */
	{PORTD7, EN_PORT_D, EN_PORT_DI}, 	 /**< EN_SID_WIFI_CONTROL_UP */
	{PORTB0, EN_PORT_B, EN_PORT_DI},	 /**< EN_SID_WIFI_CONTROL_DOWN */
	{PORTB5, EN_PORT_B, EN_PORT_DI},	 /**< EN_SID_WIFI_CONTROL_RIGHT */
	{PORTB4, EN_PORT_B, EN_PORT_DI}	     /**< EN_SID_WIFI_CONTROL_LEFT */
};


/**
 * @brief Returns status of logical Input Pin.
 *
 * Links are generated automatically for webpages (like http://www.google.co.uk)
 * and for structures, like BoxStruct_struct. For typedef-ed types use
 * #BoxStruct.
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
  * @param pinId_en logical input pin name. range: EN_INPUT_PINS
 * @return @c state of the pin.
 */



uint8_t GetInputPin (EN_INPUT_PINS pinId_en)
{	
		
	if (pinId_en>=EN_NUMBER_OF_ELEMENTS_INPUT)
{	
		
		return 0;
}	
	else
	{
		if ((matchingTableInputPins_acst[pinId_en].portType_en==EN_PORT_AI)||(matchingTableInputPins_acst[pinId_en].portType_en==EN_PORT_DI))
		{	
			
				return inputBuffer_u16[pinId_en];
				
		}	
		else
		{	
			return 0;
		}	
	}
	
	
}


/**
 * @brief Returns status of logical Output Pin.
 *
 * Links are generated automatically for webpages (like http://www.google.co.uk)
 * and for structures, like BoxStruct_struct. For typedef-ed types use
 * #BoxStruct.
 * For functions, automatic links are generated when the parenthesis () follow
 * the name of the function, like Box_The_Function_Name().
 * Alternatively, you can use #Box_The_Function_Name.
  * @param pinId_en logical output pin name. range: EN_OUPUT_PINS
 * @return @c state of the pin.
 */
void setOutputPin (EN_OUTPUT_PINS pinId_en, uint8_t value_u8) 
{

	
	if (pinId_en>=EN_NUMBER_OF_ELEMENTS_OUTPUTS) /**< tests if the pin is out of range */
	{
		// do nothing
	}
	else if (matchingTableOutputPins_acst[pinId_en].portType_en==EN_PORT_DOPWM)   /**<verificam daca portul e de tip PWM  */
		{
			/**<PWM port  */
			 if (value_u8 > MAX_PWM_VALUE)
			{
				value_u8 = MAX_PWM_VALUE; /**< sets the value to be put in output buffer to the maximum PWM value */
				
			}
			outputBuffer_u8[pinId_en]=value_u8;
			
				
					
		}
		else
		{
			/**<not a PWM port  */
			if (matchingTableOutputPins_acst[pinId_en].portType_en==EN_PORT_DO)
			{
				if(value_u8 > MAX_DIGITAL_VALUE) /**<implementat pentru robustete  */
				{
					value_u8 = MAX_DIGITAL_VALUE;
				}
				outputBuffer_u8[pinId_en] = value_u8;
				/**< functia de Set pini digitali */
			}
			else
			{
				/**<do nothing  */
			}
	}
}	

/*uint8_t getOutputs(EN_OUTPUT_PINS pinId_en){
	
		if (pinId_en>=EN_NUMBER_OF_ELEMENTS_OUTPUTS)
		{
				return outputBuffer_u8[pinId_en];
			
		}
		
	
}*/

/**
 * @brief Function implementation for processing output buffer
 *
 * Function implementation for processing output buffer
 * @return void
 */

void processOutputBuffer() {
	uint8_t bufferIndex_len;
	for(bufferIndex_len=0; bufferIndex_len<EN_NUMBER_OF_ELEMENTS_OUTPUTS; bufferIndex_len++) {
		switch (matchingTableOutputPins_acst[bufferIndex_len].portType_en)
		{
			case EN_PORT_DO: 
				processDigitalOutput((EN_OUTPUT_PINS)bufferIndex_len);								
				break; /**<end case EN_PORT_DO  */
				
			case EN_PORT_DOPWM:
				processDigitalOutputPWM((EN_OUTPUT_PINS)bufferIndex_len);
				break;
				
			default:
				break;	
		} /**< end switch port type  */
	}
	}

/**< functia pentru citirea unui pin */
int getValue(uint8_t pin){
	
	uint8_t Register; /**< variabila in care stocam valoarea registrului din care citim */

	/**< cautam registrul aferent piniului selectat, PINx de unde citim starea pinului */
	if ((0 <=pin)||(pin <=7))
	{
		Register = PIND; /**< Registrii PINx sunt Read Only */
	}
	else if((8 >=pin)||(pin <=13))
	{
		Register = PINB;
		/**< pin= pin-7; resetam pinul astfel incat sa putem citi din registrul pinB daca acesta nu e setat in memorie in continuare la PIND */
	}
	else if((14 >=pin)||(pin <=19))
	{
		Register = PINC;
		/**< pin= pin-13; */
	}

	else
	Register=NOT_A_PIN;

	/**< cautam pinul din registrul aferent,de aici putem afla starea pinilor daca sunt Input (1), sau Output (0); */
	if(CHECK_BIT(Register,pin)==1)
	{ return true;}
	else
	{return false;}
	
}



//functie de initializare pwm
void initIO()
{
	uint8_t Index_len;
	//all ports are inputs
	DDRC = 0x00;
	DDRD = 0x00;
	DDRB = 0x00;
	//set port direction to output for ports  which are defined as outputs
	for(Index_len=0; Index_len<EN_NUMBER_OF_ELEMENTS_OUTPUTS; Index_len++)
		{
			switch (matchingTableOutputPins_acst[Index_len].portName_en)
			{
				case EN_PORT_C:
					 DDRC |= (1 << matchingTableOutputPins_acst[Index_len].portVal_u8);
				break;
				case EN_PORT_B:
					 DDRB |= (1 << matchingTableOutputPins_acst[Index_len].portVal_u8);
				break;
				case EN_PORT_D:
					 DDRD |= (1 << matchingTableOutputPins_acst[Index_len].portVal_u8);
					
				break;
				
				default:
				break;
				
			}
		}
		
			TCCR2A |= (1 << COM2A1) |(1<<COM2B1);
			// set none-inverting mode

			TCCR2A |= (1 << WGM20);
			// set fast PWM Mode

			TCCR2B |= (1 << CS22) |(1 << CS21)|(1 << CS20);
			// set prescaler to 1024 and starts PWM
}


/**
 * @brief Function implementation for processing output buffer
 *
 * Function implementation for processing output buffer
 * @return void
 */

void processDigitalOutput(EN_OUTPUT_PINS bufferIndex_len) {
	switch (matchingTableOutputPins_acst[bufferIndex_len].portName_en) {
		case EN_PORT_B:
		if(outputBuffer_u8[bufferIndex_len]) {
			PORTB |= (1<<matchingTableOutputPins_acst[bufferIndex_len].portVal_u8);
			} else {
			PORTB &= ~(1<<matchingTableOutputPins_acst[bufferIndex_len].portVal_u8);
		}
		break;
		
		case EN_PORT_C:
		if(outputBuffer_u8[bufferIndex_len]) {
			PORTC |= (1<<matchingTableOutputPins_acst[bufferIndex_len].portVal_u8);
			} else {
			PORTC &= ~(1<<matchingTableOutputPins_acst[bufferIndex_len].portVal_u8);
		}
		break;
		case EN_PORT_D:
		if(outputBuffer_u8[bufferIndex_len]) {
			PORTD |= (1<<matchingTableOutputPins_acst[bufferIndex_len].portVal_u8);
			} else {
			PORTD &= ~(1<<matchingTableOutputPins_acst[bufferIndex_len].portVal_u8);
		}
		break;
		
		default:
		break;
	}
}

/**
 * @brief Function implementation for processing output buffer
 *
 * Function implementation for processing output buffer
 * @return void
 */
void processDigitalOutputPWM(EN_OUTPUT_PINS bufferIndex_len) {
	
	uint8_t tempValue_lu8;
	tempValue_lu8 = (outputBuffer_u8[bufferIndex_len] *MAX_PWM_VALUE_REG)/ MAX_PWM_VALUE;
			switch(bufferIndex_len) {
			// TODO: to be checked if correct
			case EN_SODPWM_ENABLE_MOTOR1:
				OCR2A = tempValue_lu8;
				break;
				
			case EN_SODPWM_ENABLE_MOTOR2:
			//Serial.write(DDRD);
			//analogWrite(3,tempValue_lu8);
				OCR2B =tempValue_lu8;
				break;
				
			default:
				break;
		}
}


/**
 * @brief Function implementation for processing output buffer
 *
 * Function implementation for processing output buffer
 * @return void
 */

void processInputBuffer() {
	
	
	uint8_t bufferIndex_len;
	for(bufferIndex_len=0; bufferIndex_len<EN_NUMBER_OF_ELEMENTS_INPUT; bufferIndex_len++) {
		switch (matchingTableInputPins_acst[bufferIndex_len].portType_en)
		{
			case EN_PORT_AI:
			
			processAnalogInput((EN_INPUT_PINS)bufferIndex_len);
			break; /**<end case EN_PORT_AI  */
			
			case EN_PORT_DI:
			processDigitalInput((EN_INPUT_PINS) bufferIndex_len);
			break;
			
			default:
			break;
			} /**< end switch port type  */
		}
	}

void processAnalogInput(EN_INPUT_PINS bufferIndex_len) 
{
	if(matchingTableInputPins_acst[bufferIndex_len].portType_en==EN_PORT_AI)
	{
		inputBuffer_u16[bufferIndex_len]=adc_Result_u16[matchingTableInputPins_acst[bufferIndex_len].portVal_u8];
	}
	else
	{
		/**<do nothing */
	}
}
	

void processDigitalInput(EN_INPUT_PINS bufferIndex_len)
{

	
	uint8_t tempVal_ula=0;
	
	switch (matchingTableInputPins_acst[bufferIndex_len].portName_en)
	{
		case EN_PORT_C:
		tempVal_ula=PINC;
		break;
		
		case EN_PORT_B:
		tempVal_ula=PINB;
		break;
		
		case EN_PORT_D:
		tempVal_ula=PIND;
	
		break;		
		
		default:
		break;
		
	}
	tempVal_ula &= 1<<matchingTableInputPins_acst[bufferIndex_len].portVal_u8;
	tempVal_ula = tempVal_ula>>matchingTableInputPins_acst[bufferIndex_len].portVal_u8;
	inputBuffer_u16[bufferIndex_len]=tempVal_ula;

}


/**
 * @brief Function implementation for analog input from lightsensor
 *
 * Function implementation for analog input from lightsensor
 * @return void
 */

void setupADC()
{
	uint8_t adc_index_lu8;
	
	/**<it is set the ADC enable bit*/
	/**<it is set the ADC prescaler for 128 cycles*/
	ADCSRA=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	
	//DIDR0=0;	/**< no analog input channel is yet open*/
	
	for(adc_index_lu8=0;adc_index_lu8<EN_NUMBER_OF_ELEMENTS_INPUT;adc_index_lu8++){
		if(matchingTableInputPins_acst[adc_index_lu8].portType_en==EN_PORT_AI)
		{
			DIDR0|=(1<<matchingTableInputPins_acst[adc_index_lu8].portVal_u8); /**< enables analog input channels*/
		}
		else
		{
			/**<do nothing */
		}
	}
	START_CONVERSION();
}

/**
 * @brief Function processes ADC conversion
 *
 * Function verifies enabled ADC channels and stores the ADC conversion values in an arrayf results
 * On each enabled ADC channel, the ADMUX register is updated 
 * @return void
 */
void processADCconversion()
{
	static uint8_t adc_channel_id_lu8=0;	/**< index for result ADC conversion array */
	static EN_CONVERSION_STATE conversion_state = EN_CONVERSION_IDLE;
		
	if(CHECK_BIT(DIDR0,adc_channel_id_lu8))	/**< current channel is enabled */
	{
		switch (conversion_state)
		{
			case EN_CONVERSION_IDLE:
				adc_Result_u16[adc_channel_id_lu8] = ADC;	/**< array of result gets ADC value for the specified channel */
				if(adc_channel_id_lu8<MAX_ADC_CHANNELS) 
				{
					adc_channel_id_lu8++;		/**<passes to the next ADC channel  */
					ADMUX=(ADMUX & 0xF0)|(adc_channel_id_lu8 & 0x0F); /**< updates ADMUX register */
				} else 
				{
					adc_channel_id_lu8 = 0; /**< resets the initial value */
				}
				START_CONVERSION();
				break;
			case EN_CONVERSION_IN_PROGRESS:
				if(!CHECK_BIT(ADCSRA, ADSC)) {	/**< ADSC bit is not set - meaning the ADC conversion is not in progress  */
					conversion_state = EN_CONVERSION_IDLE;
				}
				break;
			default:
				/* Your code here */
				break;
		}
	}
	else /**< current channel is NOT enabled */
	{
		if(adc_channel_id_lu8<MAX_ADC_CHANNELS)
		{
			adc_channel_id_lu8++; /**<passes to the next ADC channel  */
			ADMUX=(ADMUX & 0xF0)|(adc_channel_id_lu8 & 0x0F);/**< updates ADMUX register */
		}
		else
		{
			adc_channel_id_lu8=0;/**< resets the initial value */
		}
	}
}

	




