/*
    module  : clock.c
    version : 1.2
    date    : 05/02/22
*/
#ifndef CLOCK_C
#define CLOCK_C

/**
1130  clock  :  ->  I
Pushes the integer value of current CPU usage in milliseconds.
*/
PUSH(clock_, INTEGER_NEWNODE, (clock() - env->startclock))



#endif
