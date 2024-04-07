/*
 * clock.h
 *
 *  Created on: April 2, 2024
 *      Author: Beekman
 */
#include "stm32l4xx_hal.h"
#include "main.h"

extern WallClock Clock;

void clock_init(WallClock Clock);
void clock_increment(WallClock Clock);
void add_clocks(WallClock Clock1, WallClock Clock2);
int clock_compare(WallClock Clock1, WallClock Clock2);


