/*
 * brake.h
 *
 * Created: 5/4/2017 3:11:09 PM
 *  Author: octavian.rusu
 */ 

#pragma once

#ifndef BRAKE_H_
#define BRAKE_H_

/**
* @brief Init function of the brake functionality
*
*  Longer version of the description of the Init function of the brake functionality
* @return void
* @note Void function with no return.
*/
void brakeInit();

/**
* @brief Cyclic function of the brake functionality
*
*  Longer version of the description of the Cyclic function of the brake functionality
* @return void
* @note Void function with no return.
*/
void brakeCyclic();

/**
* @brief Implementation of function that handles the flasher brake aquisition
*
* Implementation of function that handles the brake control
* @return void
* @note Void function with no return.
*/

void brakeInputsAQ();

/**
* @brief Implementation of function that handles the flasher brake machine
*
* Implementation of function that handles the brake control
* @return void
* @note Void function with no return.
*/
void brakeSM();

/**
* @brief Implementation of function that handles the brake actuator
*
* Implementation of function that handles the brake actuator
* @return void
* @note Void function with no return.
*/
void brakeActuator();




#endif /* BRAKE_H_ */