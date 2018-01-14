/* 
* overloadnew.h
*
* Created: 1/2/2018 3:14:00 PM
* Author: tommy
*/


#ifndef __OVERLOADNEW_H__
#define __OVERLOADNEW_H__

#include <stdlib.h>

void* operator new(size_t objsize);
void operator delete(void* obj);

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);

#endif //__OVERLOADNEW_H__
