
/*
 * schedulerConfig.h
 *
 * Created: 07.07.2015 4:58:30
 *  Author: Adrian
 */ 

#ifndef SCHEDULERCONFIG_H
#define SCHEDULERCONFIG_H

/**
 * The interval in ticks to call the 20 ms tasks
 */
#define T_INTERVAL_20MS 1 

/**
 * The interval in ticks to call the 40 ms tasks
 */
#define T_INTERVAL_40MS  2 

/**
 * The interval in ticks to call the 60 ms tasks
 */
#define T_INTERVAL_60MS  3 

/**
 * The interval in ticks to call the 100 ms tasks
 */
#define T_INTERVAL_100MS  5 

/**
 * The interval in ticks to call the 1000 ms tasks
 */
#define T_INTERVAL_1000MS  50 

/**
 * The start value of the Timer                                                                       
 */
// TODO:
#define T_TIMER_START 64286

/**
 * @brief Structure used to define a task and the interval of the execution
 *
 * Structure used to define a task and the interval of the execution
 */
typedef struct {
	uint16_t interval_u16;			// defines how often a task will run
	void(*ptrFunc)(void);		    // function pointer to the task		
} TaskType_stType;

#endif // end SCHEDULERCONFIG_H