/* 
* MultiplexedLedSegnamntDisplay.cpp
*
* Created: 1/2/2018 8:26:31 PM
* Author: tommy
*/


#include "MultiplexedLedSegnamntDisplay.h"

const uint8_t MultiplexedLedSegnamntDisplay::NUMBERS_SIZE = 4;

// default constructor
MultiplexedLedSegnamntDisplay::MultiplexedLedSegnamntDisplay
(volatile uint8_t *selector_port, volatile uint8_t *selector_ddr, volatile uint8_t *display_port, volatile uint8_t * display_ddr, uint8_t *numbers) {
	*selector_ddr |= 0x0F;
	this->selector_port = selector_port;
	this->display = new LedSegmantDisplay(display_port, display_ddr);
	this->numbers = numbers;
} //MultiplexedLedSegnamntDisplay

 void MultiplexedLedSegnamntDisplay::displayNextNumber()
{
	static uint8_t numberIdx = 0;
	numberIdx = (numberIdx + 1)%NUMBERS_SIZE;
	*selector_port &= 0xF0;
	display->show(this->numbers[numberIdx], false);
	*selector_port |= _BV(numberIdx);
}

void MultiplexedLedSegnamntDisplay::turnOffDisplay() {
	*selector_port &= 0xF0;
}
