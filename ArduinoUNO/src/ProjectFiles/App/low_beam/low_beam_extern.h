/*
 * low_beam_extern.h
 *
 * Created: 04/05/2017 15:13:14
 *  Author: raul.butunoi
 */ 


#ifndef LOW_BEAM_EXTERN_H_
#define LOW_BEAM_EXTERN_H_

#include "low_beam.h"

/**
* @brief Implementation of function that handles the initialization of lowbeam control
*
* mplementation of function that handles the initialization of lowbeam control
* @return void
* @note Void function with no return.
*/
extern void lowBeamInit();


/**
* @brief Implementation of function that handles the lowbeam control
*
* Implementation of function that handles the lowbeam control
* @return void
* @note Void function with no return.
*/
extern void lowBeamCyclic();

extern int getLightsState();


#endif /* LOW_BEAM_EXTERN_H_ */