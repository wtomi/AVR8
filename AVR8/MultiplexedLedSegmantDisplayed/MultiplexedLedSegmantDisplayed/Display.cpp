/* 
* Display.cpp
*
* Created: 1/13/2018 6:09:29 PM
* Author: tommy
*/


#include "Display.h"

Display Display::instance;
static uint8_t numbers[] = {4, 3, 2, 1};
static MultiplexedLedSegnamntDisplay display(&PORTC, &DDRC, &PORTD, &DDRD, numbers);

static volatile bool faded = false;

void displayNextNumber() {
	display.displayNextNumber();
}

void turnOffDisplay() {
	display.turnOffDisplay();
}

void fadeDisplay()
{
	faded = true;
	Display::instance.timer->setCompareValue(50);
}

void unfadeDisplay()
{
	faded = false;
	Display::instance.timer->setCompareValue(255);	
}

void blinkListener() {
	if (faded) {
		unfadeDisplay();
	} else {
		fadeDisplay();
	}
}

Display::Display() {
	timer = Timer::getInstance();
	timer->addOverflowListener(displayNextNumber);
	timer->addCompareAListener(turnOffDisplay);
	timer->enableOverflowInterrupt();
	timer->enableCompareAInterrupt(255);
	timer->start();
	timer->addIntervalListener(blinkListener);
}

Display * Display::getInstance() {
	return &instance;
}

void Display::setSeconds(uint16_t seconds) {
	numbers[0] = seconds / 600;
	numbers[1] = (seconds % 600) / 60;
	numbers[2] = (seconds % 60) / 10;
	numbers[3] = seconds % 10;
}

void Display::turnOnBlinking() {
	timer->startIntervals(500);
	fadeDisplay();
}

void Display::turnOffBlinking() {
	timer->stopIntervals();
	unfadeDisplay();
}

