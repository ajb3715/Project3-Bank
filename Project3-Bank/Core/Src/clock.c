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
WallClock Clock = {.hour = 9, .minute = 0, .second = 0};


WallClock clock_init(WallClock the_clock) {
	//Initialize the main clock
	the_clock.hour = 0;
	the_clock.minute = 0;
	the_clock.second = 0;

	return the_clock;
}

WallClock day_init(WallClock the_clock) {
	//Initialize the main clock
	the_clock.hour = 9;
	the_clock.minute = 0;
	the_clock.second = 0;

	return the_clock;
}

WallClock clock_increment(WallClock the_clock){
	//Check if second is full, if so then increment
	//minute count and reset second count to 0
	//if minute count full increment hour count and reset minutes to 0
	if(the_clock.second >= 59){
		the_clock.second -= 59;
		if(the_clock.minute >= 59){
			the_clock.minute -= 59;
			the_clock.hour += 1;
		}
		else{
			the_clock.minute += 1;
		}
	}
	else{
		the_clock.second += 1;
	}
	return the_clock;
}

WallClock add_clocks(WallClock Clock1, WallClock Clock2){
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

	return Clock1;
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
	return 0;
}

WallClock subtract_Clocks(WallClock clock1, WallClock clock2) {
    WallClock result;

    // Convert both clocks to total seconds
    int totalSeconds1 = clock1.hour * 3600 + clock1.minute * 60 + clock1.second;
    int totalSeconds2 = clock2.hour * 3600 + clock2.minute * 60 + clock2.second;

    // Calculate the difference in total seconds
    int diffSeconds = totalSeconds1 - totalSeconds2;

    // Handle negative differences
    if (diffSeconds < 0) {
        diffSeconds += 24 * 3600; // Assuming clocks are within a 24-hour period
    }

    // Convert difference back to clock format
    result.hour = diffSeconds / 3600;
    diffSeconds %= 3600;
    result.minute = diffSeconds / 60;
    result.second = diffSeconds % 60;

    return result;
}



