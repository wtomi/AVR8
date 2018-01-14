/* 
* RealTimeCounter.h
*
* Created: 1/13/2018 7:39:00 PM
* Author: tommy
*/


#ifndef __REALTIMECOUNTER_H__
#define __REALTIMECOUNTER_H__

#include <avr/io.h>

#include "Timer2.h"

class RealTimeCounter
{
//variables
public:
protected:
private:
	static RealTimeCounter instance;
	Timer2 *timer;
	uint32_t seconds;

//functions
public:
	static RealTimeCounter *getInstance();
	void addSecondListener(void (*listener)());
	uint32_t getSeconds();
	void reset();
	void start();
	void stop();
protected:
private:
	RealTimeCounter();
	friend void increamentSeconds();

}; //RealTimeCounter

#endif //__REALTIMECOUNTER_H__
