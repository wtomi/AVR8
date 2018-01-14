/* 
* Timer2.h
*
* Created: 1/6/2018 7:39:09 PM
* Author: tommy
*/


#ifndef __TIMER2_H__
#define __TIMER2_H__

#include <avr/io.h>

class Timer2
{
//variables
public:
protected:
private:
	static Timer2 instance;

//functions
public:
	static Timer2 *getInstance();
	void enableExternalClock() {
		ASSR |= _BV(AS2);
	}
	void waitForRegisterUpdate() {
		while(ASSR&0x07);
	}
	void enableOverflowInterrupt() {
		TIMSK2 |= _BV(TOIE2);
	}
	void reset() {
		TCNT2 = 0;
	}
	void start() {
		TCCR2B = _BV(CS22) | _BV(CS20); //prescaler 128 which gives 1 sec for overflow with clock 32 kHz
	}
	void stop() {
		TCCR2B &= ~0x07; //reset CS20-CS22 
	}
	void addOverflowListener(void(*listener)());
protected:
private:
	Timer2();

}; //Timer2

#endif //__TIMER2_H__
