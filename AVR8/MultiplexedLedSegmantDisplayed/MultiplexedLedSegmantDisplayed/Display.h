/* 
* Display.h
*
* Created: 1/13/2018 6:09:30 PM
* Author: tommy
*/


#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <avr/io.h>

#include "Timer.h"
#include "MultiplexedLedSegnamntDisplay.h"

class Display
{
//variables
public:
protected:
private:
	static Display instance;
	Timer *timer;
	
//functions
public:
	static Display *getInstance();
	void setSeconds(uint16_t seconds);
	void turnOnBlinking();
	void turnOffBlinking();
protected:
private:
	Display();
	friend void blinkListener();
	friend void unfadeDisplay();
	friend void fadeDisplay();

}; //Display

#endif //__DISPLAY_H__
