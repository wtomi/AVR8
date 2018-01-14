/* 
* MultiplexedLedSegnamntDisplay.h
*
* Created: 1/2/2018 8:26:31 PM
* Author: tommy
*/


#ifndef __MULTIPLEXEDLEDSEGNAMNTDISPLAY_H__
#define __MULTIPLEXEDLEDSEGNAMNTDISPLAY_H__

#include <avr/io.h>
#include "LedSegmantDisplay.h"

class MultiplexedLedSegnamntDisplay
{
private:
	static const uint8_t NUMBERS_SIZE; 
	LedSegmantDisplay *display;
	uint8_t *numbers;
	volatile uint8_t *selector_port;

public:
	MultiplexedLedSegnamntDisplay(volatile uint8_t *selector_port, volatile uint8_t *selector_ddr, 
	volatile uint8_t *display_port, volatile uint8_t * display_ddr, uint8_t *numbers);
	void displayNextNumber();
	void turnOffDisplay();

}; //MultiplexedLedSegnamntDisplay

#endif //__MULTIPLEXEDLEDSEGNAMNTDISPLAY_H__
