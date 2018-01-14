/* 
* Buttons.h
*
* Created: 1/13/2018 2:14:53 PM
* Author: tommy
*/


#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Timer.h"

class Buttons
{
//variables
public:
protected:
private:
	static Buttons instance;
	Timer *timer;

//functions
public:
	static Buttons *getInstance();
	void addListenerButton1(void (*listener)());
	void addListenerButton2(void (*listener)());
	void addListenerButton3(void (*listener)());
protected:
private:
	Buttons();

}; //Buttons

#endif //__BUTTONS_H__
