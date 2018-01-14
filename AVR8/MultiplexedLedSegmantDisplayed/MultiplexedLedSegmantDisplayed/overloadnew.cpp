/* 
* overloadnew.cpp
*
* Created: 1/2/2018 3:14:00 PM
* Author: tommy
*/


#include "overloadnew.h"

void* operator new(size_t objsize) {
	return malloc(objsize);
}

void operator delete(void* obj) {
	free(obj);
}

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};
