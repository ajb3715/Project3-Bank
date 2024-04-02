/*
 * clock.h
 *
 *  Created on: April 2, 2024
 *      Author: Beekman
 */
#include "stm32l4xx_hal.h"

extern WallClock Clock;

void clock_init(void);
void clock_increment(WallClock Clock);


