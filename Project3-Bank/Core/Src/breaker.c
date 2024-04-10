/*
 * teller.c
 *
 *  Created on: April 5, 2024
 *      Author: Beekman
 */

#include "stm32l476xx.h"
#include "main.h"
#include "clock.h"
#include "teller.h"

Breaker breaker;

void init_breaker(void){
	uint32_t* random1;
	uint32_t* random2;
	uint32_t* random3;

	//What time the variable for going on break will be assigned

	breaker.start_break[0] = 0;
	//Duration of the assigned break;
	HAL_RNG_GenerateRandomNumber(&hrng,random1);
	WallClock temp_clock1 = { .hour = 9, .minute = (30 + (*random1 - 30) % 31), .second = (*random1 % 60)};
	WallClock temp_clock11 = { .hour = 0, .minute = (*random1 % 5), .second = (*random1 % 60)};
	breaker.break_time[0] = add_clocks(breaker.break_time[0],temp_clock1);
	breaker.break_duration[0] = add_clocks(breaker.break_duration[0],temp_clock11);

	//What time the variable for going on break will be assigned
	breaker.start_break[1] = 0;
	//Duration of the assigned break;
	HAL_RNG_GenerateRandomNumber(&hrng,random2);
	WallClock temp_clock2 = { .hour = 9, .minute = (30 + (*random2 - 30) % 31), .second = (*random2 % 60)};
	WallClock temp_clock22 = { .hour = 0, .minute = (*random2 % 5), .second = (*random2 % 60)};
	breaker.break_time[0] = add_clocks(breaker.break_time[1],temp_clock2);
	breaker.break_duration[0] = add_clocks(breaker.break_duration[1],temp_clock22);
	//What time the variable for going on break will be assigned
	breaker.start_break[2] = 0;
	//Duration of the assigned break;
	HAL_RNG_GenerateRandomNumber(&hrng,random3);
	WallClock temp_clock3 = { .hour = 9, .minute = (30 + (*random3 - 30) % 31), .second = (*random3 % 60)};
	WallClock temp_clock33 = { .hour = 0, .minute = (*random3 % 5), .second = (*random3 % 60)};
	breaker.break_time[0] = add_clocks(breaker.break_time[1],temp_clock3);
	breaker.break_duration[0] =  add_clocks(breaker.break_duration[1],temp_clock33);
}

void run_breaker(){
	uint32_t* random1;
	uint32_t* random2;
	uint32_t* random3;

	//Override automatic break if switch gets pressed
	if((!HAL_GPIO_ReadPin(Switch1_GPIO_Port, Switch1_Pin)) == 1 ){
		breaker.start_break[0] = 1;
	}
	if((!HAL_GPIO_ReadPin(Switch1_GPIO_Port, Switch1_Pin)) == 1 ){
		breaker.start_break[0] = 1;
	}
	if((!HAL_GPIO_ReadPin(Switch1_GPIO_Port, Switch1_Pin)) == 1 ){
		breaker.start_break[0] = 1;
	}


}

//TODO Implement manual function for the buttons for breaks
