/*
* LedSegmantDisplay.cpp
*
* Created: 12/31/2017 6:04:04 PM
* Author: tommy
*/


#include "LedSegmantDisplay.h"

const uint8_t LedSegmantDisplay::DIGITS_SIZE = 10;
const uint8_t LedSegmantDisplay::DIGITS[DIGITS_SIZE] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
const uint8_t LedSegmantDisplay::DOT_POINT = 0x80;

LedSegmantDisplay::LedSegmantDisplay(volatile uint8_t *port, volatile uint8_t *ddr) {
	*ddr = 0xFF;
	this->port = port;
}

void LedSegmantDisplay::show(uint8_t digit, bool dotPoint) {
	uint8_t digitToDisplay = 0xFF;
	if(digit < DIGITS_SIZE) {
		digitToDisplay = DIGITS[digit];
	}
	if(dotPoint) {
		digitToDisplay &= ~DOT_POINT;
	}
	*port = digitToDisplay;
}
