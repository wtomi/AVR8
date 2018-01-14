/* 
* Timer.cpp
*
* Created: 1/1/2018 11:56:33 PM
* Author: tommy
*/


#include "Timer.h"
#include <avr/interrupt.h>
#include <stdlib.h>

static const uint32_t PRESCALER = 8;
static const uint32_t TICKS_PER_MS = F_CPU / PRESCALER / 1000;
static const uint8_t MAX_COUNT = 0xFF;
static volatile uint32_t numberOfOverflows;
static volatile uint32_t overflowCounter;

static const uint8_t MAX_OVERFLOW_LISTENERS = 5;
static void (*globalOverflowListeners[MAX_OVERFLOW_LISTENERS])();
static volatile uint8_t overflowListenerCount = 0;
static void (*globalCompareAListener)();
static void (*globalIntervalListener)();

Timer Timer::instance;

// default constructor
Timer::Timer() {
} //Timer

Timer *Timer::getInstance() {
	return &Timer::instance;
}

void Timer::addOverflowListener(void(*listener)()) {
	if(overflowListenerCount < MAX_OVERFLOW_LISTENERS) {
		globalOverflowListeners[overflowListenerCount++] = listener;
	}
}

void Timer::addCompareAListener(void(*listener)()) {
	globalCompareAListener = listener;
}

void Timer::enableOverflowInterrupt() {
	TIMSK0 |= _BV(TOIE0); //Timer Overflow Interrupt Enable
}

void Timer::enableCompareAInterrupt(uint8_t compareValue) {
	TIMSK0 |= _BV(OCIE0A);
	OCR0A = compareValue;
}

void Timer::setCompareValue(uint8_t compareValue) {
	OCR0A = compareValue;
}

void Timer::start() {
	TCCR0B = _BV(CS01); //Set prescaler to 8
}

void Timer::addIntervalListener(void(*listener)()) {
	globalIntervalListener = listener;
}

void Timer::startIntervals(uint32_t millis) {
	uint32_t ticks = millis * TICKS_PER_MS;
	uint8_t offset = ticks % MAX_COUNT;
	numberOfOverflows = ticks / MAX_COUNT;
	overflowCounter = 0;
	OCR0B = offset;
	TCNT0 = 0x00;
	TIFR0 |= _BV(OCF0B) | _BV(TOV0);
	TIMSK0 |= _BV(OCIE0B) | _BV(TOIE0);
}

void Timer::stopIntervals() {
	TIMSK0 &= ~_BV(OCIE0B);
}

ISR(TIMER0_OVF_vect) {
	overflowCounter++;
	for(uint8_t i = 0; i < overflowListenerCount; i++) {
		globalOverflowListeners[i]();	
	}
}

ISR(TIMER0_COMPA_vect) {
	globalCompareAListener();
}

ISR(TIMER0_COMPB_vect) {
	if(overflowCounter >= numberOfOverflows) {
		overflowCounter = 0;
		TCNT0 = 0x00;
		globalIntervalListener();
	}
}