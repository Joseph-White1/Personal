// Example program #2 from Chapter 13 of Absolute Beginner's Guide
// to C, 3rd Edition
// File Chapter13ex2.c

/* This program increases a counter from 1 to 5, printing updates
and then counts it back down to 1. However, it uses the increment
and decrement operators */

#include "../sample_code.h"
void chap13ex2(void){
    int ctr = 0;

    printf("Counter is at %d.\n", ++ctr);
    printf("Counter is at %d.\n", ++ctr);
    printf("Counter is at %d.\n", ++ctr);
    printf("Counter is at %d.\n", ++ctr);
    printf("Counter is at %d.\n", ++ctr);
    printf("Counter is at %d.\n", --ctr);
    printf("Counter is at %d.\n", --ctr);
    printf("Counter is at %d.\n", --ctr);
    printf("Counter is at %d.\n", --ctr);
}