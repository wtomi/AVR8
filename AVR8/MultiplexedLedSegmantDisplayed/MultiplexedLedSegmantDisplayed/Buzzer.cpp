/* 
* Buzzer.cpp
*
* Created: 1/13/2018 3:22:07 PM
* Author: tommy
*/


#include "Buzzer.h"

Buzzer Buzzer::instance;

// default constructor
Buzzer::Buzzer() {
	this->timer = Timer16::getInstance();
	this->timer->setPWNAFastMode(128);
	this->timer->start();
} //Buzzer

Buzzer * Buzzer::getInstance() {
	return &Buzzer::instance;
}

void stopBeep() {
	Buzzer::instance.timer->stopPWMA();
}

void Buzzer::beep(uint32_t millis) {
	timer->startPWMA();
	timer->notifyAfter(stopBeep, millis);
}


