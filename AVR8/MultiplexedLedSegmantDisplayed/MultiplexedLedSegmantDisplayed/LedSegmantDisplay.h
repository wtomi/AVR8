/*
* LedSegmantDisplay.h
*
* Created: 12/31/2017 6:04:04 PM
* Author: tommy
*/


#ifndef __LEDSEGMANTDISPLAY_H__
#define __LEDSEGMANTDISPLAY_H__

#include <avr/io.h>

class LedSegmantDisplay
{
	private:
		static const uint8_t DIGITS_SIZE;
		static const uint8_t DIGITS[];
		static const uint8_t DOT_POINT;
		volatile uint8_t *port;
	
	public:
		LedSegmantDisplay(volatile uint8_t *port, volatile uint8_t *ddr);
		void show(uint8_t value, bool dotPoint);
}; //LedSegmantDisplay

#endif //__LEDSEGMANTDISPLAY_H__
