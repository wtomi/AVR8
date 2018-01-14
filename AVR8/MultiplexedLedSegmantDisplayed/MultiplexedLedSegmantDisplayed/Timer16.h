/* 
* Timer16.h
*
* Created: 1/6/2018 5:29:21 PM
* Author: tommy
*/


#ifndef __TIMER16_H__
#define __TIMER16_H__

#include <avr/io.h>
#include <avr/interrupt.h>

class Timer16
{
//variables
public:
protected:
private:
	static Timer16 instance;

//functions
public:
	static Timer16 *getInstance();
	void start();
	void setPWNAFastMode(uint8_t width);
	void startPWMA();
	void stopPWMA();
	void setWidth(uint8_t width);
	void notifyAfter(void (*listener)(), uint32_t millis);
protected:
private:
	Timer16();

}; //Timer16

#endif //__TIMER16_H__
