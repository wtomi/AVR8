/* 
* Buttons.cpp
*
* Created: 1/13/2018 2:14:53 PM
* Author: tommy
*/


#include "Buttons.h"

void (* globalListenerButton1)();
void (* globalListenerButton2)();
void (* globalListenerButton3)();

Buttons Buttons::instance;

static volatile uint8_t overflowCount;
static const uint8_t OVERFLOW_READ = 80; //waiting about 20 ms before reading buttons' states
static volatile bool waitForRead = false; 

void overflowListener() {
	if(waitForRead) {
		overflowCount++;
		if(overflowCount >= OVERFLOW_READ) {
			waitForRead = false;
			uint8_t state = ~PINB;
			if(state & _BV(PB3)) {
				globalListenerButton1();
			} else if (state & _BV(PB4)) {
				globalListenerButton2();
			} else if (state & _BV(PB5)) {
				globalListenerButton3();
			}
		}
	}
}

 Buttons::Buttons() {
	PORTB |= _BV(PB5) | _BV(PB4) | _BV(PB3);
	PCICR |= _BV(PCIE0);
	PCMSK0 |= _BV(PCINT5) | _BV(PCINT4) | _BV(PCINT3);
	timer = Timer::getInstance();
	timer->addOverflowListener(overflowListener);
}

Buttons * Buttons::getInstance() {
	return &Buttons::instance;
}

void Buttons::addListenerButton1(void (*listener)()) {
	globalListenerButton1 = listener;
}

void Buttons::addListenerButton2(void (*listener)()) {
	globalListenerButton2 = listener;
}

void Buttons::addListenerButton3(void (*listener)()) {
	globalListenerButton3 = listener;
}

ISR(PCINT0_vect) {
	if(!waitForRead) {
		waitForRead = true;
		overflowCount = 0;
	}
}

