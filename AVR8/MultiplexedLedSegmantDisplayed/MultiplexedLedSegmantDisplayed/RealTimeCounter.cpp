/* 
* RealTimeCounter.cpp
*
* Created: 1/13/2018 7:38:59 PM
* Author: tommy
*/


#include "RealTimeCounter.h"

static void (*globalSecondListener)();

RealTimeCounter RealTimeCounter::instance;

void increamentSeconds() {
	RealTimeCounter::instance.seconds++;
	globalSecondListener();
}

RealTimeCounter::RealTimeCounter() {
	timer = Timer2::getInstance();
	timer->enableExternalClock();
	timer->reset();
	timer->waitForRegisterUpdate();
	timer->addOverflowListener(increamentSeconds);
	timer->enableOverflowInterrupt();
}

RealTimeCounter * RealTimeCounter::getInstance() {
	return &RealTimeCounter::instance;
}

void RealTimeCounter::addSecondListener(void (*listener)()) {
	globalSecondListener = listener;
}

uint32_t RealTimeCounter::getSeconds() {
	return seconds;
}

void RealTimeCounter::reset() {
	seconds = 0;
	timer->reset();
}

void RealTimeCounter::start() {
	timer->start();
}

void RealTimeCounter::stop() {
	timer->stop();
}
