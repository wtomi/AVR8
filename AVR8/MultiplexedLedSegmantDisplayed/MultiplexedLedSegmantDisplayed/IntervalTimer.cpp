/* 
* IntervalTimer.cpp
*
* Created: 1/13/2018 1:26:41 PM
* Author: tommy
*/


#include "IntervalTimer.h"

static const uint32_t INTERVAL = 15;
static const uint32_t MAX_TIME = 99 * 60 + 59;
static const uint32_t MIN_TIME_BREAK = 0;
static const uint32_t MIN_TIME_ROUND = INTERVAL;
static const uint32_t MIN_CYCLES = 1;
static const uint32_t MAX_CYCLES = 9999;

static const uint32_t SHORT_BEEP = 200;
static const uint32_t LONG_BEEP = 1000;

IntervalTimer IntervalTimer::instance;

static bool isRound = true; 
static uint16_t roundCount = 0;

void buttonStopListener() {
	IntervalTimer *intervalTimer = IntervalTimer::getInstance();
	switch (intervalTimer->state) {
		case IntervalTimer::SETTING_ROUND:
			if (intervalTimer->roundSeconds >= MIN_TIME_ROUND + INTERVAL) {
				intervalTimer->roundSeconds -= INTERVAL;
			}
			intervalTimer->display->setSeconds(intervalTimer->roundSeconds);
			break;
		case IntervalTimer::SETTING_BREAK:
			if (intervalTimer->breakSeconds >= MIN_TIME_BREAK + INTERVAL) {
				intervalTimer->breakSeconds -= INTERVAL;
			}
			
			intervalTimer->display->setSeconds(intervalTimer->breakSeconds);
			break;
		case IntervalTimer::SETTING_CYCLES:
			if (intervalTimer->numberOfCycles >= MIN_CYCLES + 1) {
				intervalTimer->numberOfCycles -= 1;
			}
			intervalTimer->display->setSeconds(intervalTimer->numberOfCycles);
			break;
		case IntervalTimer::READY:
			intervalTimer->buzzer->beep(SHORT_BEEP);
			intervalTimer->resetIntervalTimer();
			break;
	}
}

void buttonSetListener() {
	IntervalTimer *intervalTimer = IntervalTimer::getInstance();
	switch (intervalTimer->state) {
		case IntervalTimer::SETTING_ROUND:
			intervalTimer->buzzer->beep(SHORT_BEEP);
			intervalTimer->display->setSeconds(intervalTimer->breakSeconds);
			intervalTimer->state = IntervalTimer::SETTING_BREAK;
			break;
		case IntervalTimer::SETTING_BREAK:
			intervalTimer->buzzer->beep(SHORT_BEEP);
			intervalTimer->display->setSeconds(intervalTimer->numberOfCycles);
			intervalTimer->state = IntervalTimer::SETTING_CYCLES;
			break;
		case IntervalTimer::SETTING_CYCLES:
			intervalTimer->buzzer->beep(SHORT_BEEP);
			intervalTimer->display->turnOffBlinking();
			intervalTimer->display->setSeconds(intervalTimer->roundSeconds);
			intervalTimer->state = IntervalTimer::READY;
			break;
		case IntervalTimer::READY:
			intervalTimer->buzzer->beep(SHORT_BEEP);
			intervalTimer->display->turnOnBlinking();
			intervalTimer->resetIntervalTimer();
			intervalTimer->state = IntervalTimer::SETTING_ROUND;
			break;
	}
}

void buttonStartListener() {
	IntervalTimer *intervalTimer = IntervalTimer::getInstance();
	switch (intervalTimer->state) {
		case IntervalTimer::SETTING_ROUND:
			if (intervalTimer->roundSeconds + INTERVAL <= MAX_TIME) {
				intervalTimer->roundSeconds += INTERVAL;
			}
			intervalTimer->display->setSeconds(intervalTimer->roundSeconds);
			break;
		case IntervalTimer::SETTING_BREAK:
			if (intervalTimer->breakSeconds + INTERVAL <= MAX_TIME) {
				intervalTimer->breakSeconds += INTERVAL;
			}
			intervalTimer->display->setSeconds(intervalTimer->breakSeconds);
			break;
		case IntervalTimer::SETTING_CYCLES:
			if (intervalTimer->numberOfCycles + 1 <= MAX_CYCLES) {
				intervalTimer->numberOfCycles += 1;
			}
			intervalTimer->display->setSeconds(intervalTimer->numberOfCycles);
			break;
		case IntervalTimer::READY:
			intervalTimer->buzzer->beep(SHORT_BEEP);
			intervalTimer->rtc->start();
			intervalTimer->display->setSeconds(intervalTimer->roundSeconds - intervalTimer->rtc->getSeconds());
			intervalTimer->state = IntervalTimer::WORKING;
			break;
		case IntervalTimer::WORKING:
			intervalTimer->buzzer->beep(SHORT_BEEP);
			intervalTimer->rtc->stop();
			intervalTimer->state = IntervalTimer::READY;
			break;
	}
}

void IntervalTimer::resetIntervalTimer()
{
	rtc->stop();
	rtc->reset();
	display->setSeconds(roundSeconds);
	roundCount = 0;
	isRound = true;
}

void secondListener() {
	static const uint32_t SEC_TO_BEEP = 5;
	RealTimeCounter *rtc = IntervalTimer::instance.rtc;
	Display *display = IntervalTimer::instance.display;
	IntervalTimer *intervalTimer = IntervalTimer::getInstance();
	
	if (intervalTimer->state == IntervalTimer::WORKING) {
		if (isRound) {
			uint32_t secondsLeft = intervalTimer->roundSeconds - rtc->getSeconds();
			display->setSeconds(secondsLeft);
			if (secondsLeft == 0) {
				intervalTimer->buzzer->beep(LONG_BEEP);
				isRound = false;
				intervalTimer->rtc->reset();
			} else if (secondsLeft < SEC_TO_BEEP) {
				intervalTimer->buzzer->beep(SHORT_BEEP);
			}
			bool noBreak = intervalTimer->breakSeconds == MIN_TIME_BREAK;
			if(!isRound && noBreak) {
				isRound = true;
				roundCount++;
			}
		} else {
			uint32_t secondsLeft = intervalTimer->breakSeconds - rtc->getSeconds(); 
			display->setSeconds(secondsLeft);
			if (secondsLeft == 0) {
				intervalTimer->buzzer->beep(LONG_BEEP);
				isRound = true;
				intervalTimer->rtc->reset();
				roundCount++;
			} else if (secondsLeft < SEC_TO_BEEP) {
				intervalTimer->buzzer->beep(SHORT_BEEP);
			}
		}
	}
	if (roundCount == intervalTimer->numberOfCycles ) {
		intervalTimer->resetIntervalTimer();
		intervalTimer->state = IntervalTimer::READY;
	}
	
}

IntervalTimer *IntervalTimer::getInstance() {
	return &IntervalTimer::instance;
}

IntervalTimer::IntervalTimer() {
	this->state = READY;
	this->roundSeconds = MIN_TIME_ROUND;
	this->breakSeconds = MIN_TIME_BREAK;
	this->numberOfCycles = MIN_CYCLES;
	
	buttons = Buttons::getInstance();
	buzzer = Buzzer::getInstance();
	display = Display::getInstance();
	rtc = RealTimeCounter::getInstance();
	buttons->addListenerButton1(buttonStopListener);
	buttons->addListenerButton2(buttonSetListener);
	buttons->addListenerButton3(buttonStartListener);
	rtc->addSecondListener(secondListener);
	display->setSeconds(roundSeconds);
} 
