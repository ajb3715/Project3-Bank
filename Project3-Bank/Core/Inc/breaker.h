/*
 * teller.h
 *
 *  Created on: April 5, 2024
 *      Author: Beekman
 */

#include "stm32l476xx.h"
#include "main.h"
#include "clock.h"
#include "teller.h"

extern Breaker breaker;


void init_breaker(void);
void run_breaker();
