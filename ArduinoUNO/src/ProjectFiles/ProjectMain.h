/*
 * ProjectMain.h
 *
 * Created: 5/26/2015 2:21:47 PM
 *  Author: barna.peto
 */ 


#ifndef PROJECTMAIN_H_
#define PROJECTMAIN_H_



/*Include Arduino headers*/
#include <Arduino.h>

#define ARDUINO_MAIN

/*Uncomment this to disable debug through serial port*/
#define ENABLE_DEBUG 

#ifdef ENABLE_DEBUG
/**
 * @brief Add debug data to buffer that will be sent out through serial port
 * 
 * Implementation of the function that handle timer1 overflow ISR
 * @return 0: not success, 1: success
 *  
 */	
uint8_t AddSerialDebugData(uint8_t Value_lu8);


/**
 * @brief Function will try to send out debug info through serial port
 * * 
 * @return void
 *  
 */
void processSerialDebugData();
#endif



// Disable some warnings for the Arduino files
#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wsign-compare"
//#pragma GCC diagnostic ignored "-Wattributes"
//#pragma GCC diagnostic ignored "-Wunused-variable"
//#pragma GCC diagnostic ignored "-Wuninitialized"


/*
* Libraries
*/
// Standard Arduino source files for serial:
//#include <HardwareSerial.h>
// Restore original warnings configuration
// Standard Arduino source files for serial:
#include <HardwareSerial.h>

// Unused source files:
//#include <WInterrupts.c>
//#include <wiring_pulse.c>
//#include <wiring_shift.c>
//#include <IPAddress.cpp>
//#include <Tone.cpp>
#pragma GCC diagnostic pop


/**
 * @brief Function declaration for tasks which are executed every 20ms
 * Function declaration for tasks which are executed every 20ms.
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void task20ms(void);

/**
 * @brief Function declaration for tasks which are executed every40ms
 * Function declaration for tasks which are executed every 40ms
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void task40ms(void);

/**
 * @brief Function declaration for tasks which are executed every 60ms
 * Function declaration for tasks which are executed every 60ms.
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void task60ms(void);

/**
 * @brief Function declaration for tasks which are executed every 100ms
 * Function declaration for tasks which are executed every 100ms
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void task100ms(void);

/**
 * @brief Function declaration for tasks which are executed every 1000ms
 * Function declaration for tasks which are executed every 1000ms
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
 */
void task1000ms(void);

/** HEAD
 * Function prototype
 * Initialize the timer0 for ADC conversion
 */
void timer0_init();
/** 
 * Function prototype
 * Initialize the timer1 
=======
*
 * @brief Function definition for timer initialization
 * Function implementation for timer initialization.
 * Alternatively, you can use #Box_The_Function_Name.
 * @return void
>>>>>>> 558e0ec9797d9908c34a8d271e1e2aeb7cc47775
 */
void timer1_init();

extern uint8_t AddSerialDebugData(uint8_t Value_lu8);

#endif /* PROJECTMAIN_H_ */