/*
 * clock.h
 *
 *  Created on: April 2, 2024
 *      Author: Beekman
 */
#include "stm32l4xx_hal.h"
#include "main.h"

extern WallClock Clock;

WallClock clock_init(WallClock the_clock);
WallClock clock_increment(WallClock the_clock);
WallClock day_init(WallClock the_clock);
WallClock add_clocks(WallClock Clock1, WallClock Clock2);
WallClock subtract_Clocks(WallClock clock1, WallClock clock2);
WallClock average_time(WallClock avgClock, int number);
int clock_compare(WallClock Clock1, WallClock Clock2);


