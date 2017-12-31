/*
 * LedDisplay.cpp
 *
 * Created: 12/31/2017 5:20:01 PM
 * Author : tommy
 */ 

#include "LedSegmantDisplay.h"

int main(void)
{
	LedSegmantDisplay display(&PORTD, &DDRD);
	
	uint8_t number = 0;
	while (1)
	{
		display.show(number, false);
		number = (number + 1)%11;
		_delay_ms(1000);
	}
}

