/* 
* Timer.h
*
* Created: 1/1/2018 11:56:33 PM
* Author: tommy
*/


#ifndef __TIMER_H__
#define __TIMER_H__

#include <avr/io.h>

#define NULL 0

class Timer
{
//variables
private:
	static Timer instance;

//functions
public:
	static Timer *getInstance();
	void addOverflowListener(void(*listener)());
	void addCompareAListener(void(*listener)());
	void enableOverflowInterrupt();
	void enableCompareAInterrupt(uint8_t compareValue);
	void setCompareValue(uint8_t compareValue);
	void start();
	void addIntervalListener(void(*listener)());
	void startIntervals(uint32_t millis);
	void stopIntervals();
private:
	Timer();

}; //Timer

#endif //__TIMER_H__
