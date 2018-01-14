/*
* Timer16.cpp
*
* Created: 1/6/2018 5:29:20 PM
* Author: tommy
*/


#include "Timer16.h"

static const uint32_t PRESCALER = 64;
static const uint32_t TICKS_PER_MS = F_CPU / PRESCALER / 1000;
static const uint8_t MAX_COUNT = 0xFF;
static uint32_t numberOfOverflows;
static uint32_t overflowCounter;

void (*globalLister)();

Timer16 Timer16::instance;

Timer16 * Timer16::getInstance() {
	return &Timer16::instance;
}

void Timer16::start() {
	TCCR1B |= _BV(CS10) | _BV(CS11);
}

void Timer16::setPWNAFastMode(uint8_t width) {
	OCR1A = width;
	TCCR1A |= _BV(WGM10);
	TCCR1B |= _BV(WGM12);
	DDRB |= _BV(PB1);
}

void Timer16::startPWMA() {
	TCCR1A |= _BV(COM1A1);
}

void Timer16::stopPWMA() {
	TCCR1A &= ~_BV(COM1A1);
}

void Timer16::setWidth(uint8_t width) {
	OCR1A = width;
}

void Timer16::notifyAfter(void (*listener)(), uint32_t millis) {
	globalLister = listener;
	uint32_t ticks = millis * TICKS_PER_MS;
	uint8_t offset = ticks % MAX_COUNT;
	numberOfOverflows = ticks / MAX_COUNT;
	overflowCounter = 0;
	OCR1B = offset;
	TCNT1 = 0x0000;
	TIFR1 |= _BV(OCF1B) | _BV(TOV1);
	TIMSK1 |= _BV(OCIE1B) | _BV(TOIE1);
}

// default constructor
Timer16::Timer16()
{
} //Timer16

ISR(TIMER1_OVF_vect) {
	overflowCounter++;
}

ISR(TIMER1_COMPB_vect) {
	if(overflowCounter >= numberOfOverflows) {
		globalLister();
		TIMSK1 &= ~_BV(OCIE1B) & ~_BV(TOIE1);
	}
}
