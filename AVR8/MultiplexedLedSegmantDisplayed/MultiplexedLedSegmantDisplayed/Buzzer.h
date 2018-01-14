/* 
* Buzzer.h
*
* Created: 1/13/2018 3:22:07 PM
* Author: tommy
*/


#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "Timer16.h"

class Buzzer
{
//variables
public:
protected:
private:
	static Buzzer instance;
	Timer16 *timer;
	
//functions
public:
	static Buzzer * getInstance();
	void beep(uint32_t millis);
protected:
private:
	Buzzer();
	friend void stopBeep();

}; //Buzzer

#endif //__BUZZER_H__
