/*
 * clock.c
 *
 *  Created on: Jul 16, 2021
 *      Author: rickweil
 */


#include "stm32l476xx.h"
#include "main.h"

//The main clock to be checked by the program
//Declare extern within the header file
WallClock Clock = { .hour = 0, .minute = 0, .second = 0};


void clock_init(void) {
	//Initialize the main clock
	Clock.hour = 9;
	Clock.minute = 0;
	Clock.second = 0;
}

void clock_increment(WallClock Clock){
	//Check if second is full, if so then increment
	//minute count and reset second count to 0
	//if minute count full increment hour count and reset minutes to 0
	if(Clock.second == 59){
		Clock.second = 0;
		if(Clock.minute == 59){
			Clock.minute = 0;
			Clock.hour += 1;
		}
		else{
			Clock.minute += 1;
		}
	}
	else{
		Clock.second += 1;
	}
}



