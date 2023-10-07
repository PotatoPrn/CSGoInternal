#ifndef CSGOINTERNAL_MAINTHREAD_H
#define CSGOINTERNAL_MAINTHREAD_H

#include "main.h"


#define DbgPrint(x, y) std::cout << #x << y << "\n"

// Key State Definitions
#define KEYDOWN -32768
#define KEYUP 0


void HackThread();

#endif //CSGOINTERNAL_MAINTHREAD_H