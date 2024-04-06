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
	Clock.hour = 0;
	Clock.minute = 0;
	Clock.second = 0;
}

void day_init(WallClock Clock) {
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

void add_clocks(WallClock Clock1, WallClock Clock2){
	//Adds seconds then minutes then hours, accounting for overflows as needed
	//Add seconds and account overflow
	Clock1.second += Clock2.second;
	if(Clock1.second >= 60){
		Clock1.minute += 1;
		Clock1.second -= 60;
		if(Clock1.minute >= 60){
			Clock1.hour += 1;
			Clock1.minute -= 60;
		}
	}
	//Add minutes and account overflow
	Clock1.minute += Clock2.minute;
	if(Clock1.minute >= 60){
		Clock1.hour += 1;
		Clock1.minute -= 60;
	}
	//Add hours, don't account overflow as impossible
	Clock1.hour += Clock2.hour;
}

//if clock 1 is greater than clock 2(later) then return 0
//if clock 1 is less than clock 2(earlier) then return 2
int clock_compare(WallClock Clock1, WallClock Clock2){
	if(Clock1.hour == Clock2.hour){
		if(Clock1.minute == Clock2.minute){
			if(Clock1.second == Clock2.second){
				return 1;
			}
			else if(Clock1.second > Clock2.second){
				return 0;
			}
			else if(Clock1.second < Clock2.second){
				return 2;
			}
		}
		else if(Clock1.minute > Clock2.minute){
			return 0;
		}
		else if(Clock1.minute < Clock2.minute){
			return 2;
		}
	}
	else if(Clock1.hour > Clock2.hour){
		return 0;
	}
	else if(Clock1.hour < Clock2.hour){
		return 2;
	}
}



