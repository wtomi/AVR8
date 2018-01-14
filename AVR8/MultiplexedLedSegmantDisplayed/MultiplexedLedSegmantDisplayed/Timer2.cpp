/* 
* Timer2.cpp
*
* Created: 1/6/2018 7:39:09 PM
* Author: tommy
*/


#include "Timer2.h"
#include <avr/interrupt.h>

static void (*globalOverflowListener)();

Timer2 Timer2::instance; 

Timer2 * Timer2::getInstance() {
	return &instance;
}

void Timer2::addOverflowListener(void(*listener)()) {
	globalOverflowListener = listener;
}

// default constructor
Timer2::Timer2() {
} //Timer2


ISR(TIMER2_OVF_vect) {
	globalOverflowListener();
}