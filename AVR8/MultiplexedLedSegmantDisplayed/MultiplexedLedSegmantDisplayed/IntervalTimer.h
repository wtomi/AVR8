/* 
* IntervalTimer.h
*
* Created: 1/13/2018 1:26:41 PM
* Author: tommy
*/


#ifndef __INTERVALTIMER_H__
#define __INTERVALTIMER_H__

#include <avr/io.h>

#include "Buttons.h"
#include "Buzzer.h"
#include "Display.h"
#include "RealTimeCounter.h"

class IntervalTimer
{
//variables
public:
protected:
private:
	enum State {
			SETTING_ROUND,
			SETTING_BREAK,
			SETTING_CYCLES,
			READY,
			WORKING
		};
	static IntervalTimer instance; 
	State state;
	uint16_t roundSeconds;
	uint16_t breakSeconds;
	uint16_t numberOfCycles;
	Buttons *buttons;
	Buzzer *buzzer;
	Display *display;
	RealTimeCounter *rtc;

//functions
public:
	static IntervalTimer *getInstance();
	void stop();
	void start();
	void setRoundSeconds();
	void setBreakSeconds();
	void setNumberOfCycles();
protected:
private:
	IntervalTimer();
	void resetIntervalTimer();
	friend void buttonStopListener();
	friend void buttonSetListener();
	friend void buttonStartListener();
	friend void secondListener();
	

}; //IntervalTimer

#endif //__INTERVALTIMER_H__
