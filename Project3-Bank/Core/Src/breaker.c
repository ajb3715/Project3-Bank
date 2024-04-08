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
uint32_t* random1;
uint32_t* random2;
uint32_t* random3;



void init_breaker(void){
	//What time the variable for going on break will be assigned
	breaker.start_break[0] = 0;
	breaker.start_break[1] = 0;
	//Duration of the assigned break;
	HAL_RNG_GenerateRandomNumber(&hrng,random1);
	WallClock temp_clock1 = { .hour = 0, .minute = (30 + (*random1 - 30) % 31), .second = (*random1 % 60)};
	breaker.break_time1 = add_clocks(breaker.break_time1,Clock);
	breaker.break_time1 = add_clocks(breaker.break_time1,temp_clock1);
	breaker.break_duration1.hour = 0;
	breaker.break_duration1.minute = (*random1 % 5);
	breaker.break_duration1.second = (*random1 % 60);

	//What time the variable for going on break will be assigned
	breaker.start_break[2] = 0;
	//Duration of the assigned break;
	HAL_RNG_GenerateRandomNumber(&hrng,random2);
	WallClock temp_clock2 = { .hour = 0, .minute = (30 + (*random2 - 30) % 31), .second = (*random2 % 60)};
	breaker.break_time2 = add_clocks(breaker.break_time2,Clock);
	breaker.break_time2 = add_clocks(breaker.break_time2,temp_clock2);
	breaker.break_duration2.hour = 0;
	breaker.break_duration2.minute = (*random2 % 5);
	breaker.break_duration2.second = (*random2 % 60);
	//What time the variable for going on break will be assigned
	breaker.start_break[3] = 0;
	//Duration of the assigned break;
	HAL_RNG_GenerateRandomNumber(&hrng,random3);
	WallClock temp_clock3 = { .hour = 0, .minute = (30 + (*random3 - 30) % 31), .second = (*random3 % 60)};
	breaker.break_time3 = add_clocks(breaker.break_time3,Clock);
	breaker.break_time3 = add_clocks(breaker.break_time3,temp_clock3);
	breaker.break_duration3.hour = 0;
	breaker.break_duration3.minute = (*random3 % 5);
	breaker.break_duration3.second = (*random3 % 60);
}

void run_breaker(){
	if((!HAL_GPIO_ReadPin(Switch1_GPIO_Port, Switch1_Pin)) == 1 ){
			  tellers[1].take_break = 1;
	}
	if((!HAL_GPIO_ReadPin(Switch2_GPIO_Port, Switch2_Pin)) == 1 ){
			  tellers[2].take_break = 2;
	}
	if((!HAL_GPIO_ReadPin(Switch3_GPIO_Port, Switch2_Pin)) == 1 ){
			  tellers[3].take_break = 3;
	}
	if(clock_compare(Clock, breaker.break_time1) == 1){
		tellers[1].take_break = 1;
	}
	if(clock_compare(Clock, breaker.break_time2) == 1){
		tellers[2].take_break = 1;
	}
	if(clock_compare(Clock, breaker.break_time3) == 1){
		tellers[3].take_break = 1;
	}
	if(breaker.start_break[1] == 1){
		breaker.start_break[1] = 0;
		HAL_RNG_GenerateRandomNumber(&hrng,random1);
		WallClock temp_clock1 = { .hour = 0, .minute = (30 + (*random1 - 30) % 31), .second = (*random1 % 60)};
		breaker.break_time1 = add_clocks(breaker.break_time1,Clock);
		breaker.break_time1 = add_clocks(breaker.break_time1,temp_clock1);
		breaker.break_duration1.hour = 0;
		breaker.break_duration1.minute = (*random1 % 5);
		breaker.break_duration1.second = (*random1 % 60);
	}
	if(breaker.start_break[2] == 1){
		breaker.start_break[2] = 0;
		HAL_RNG_GenerateRandomNumber(&hrng,random2);
		WallClock temp_clock2 = { .hour = 0, .minute = (30 + (*random2 - 30) % 31), .second = (*random2 % 60)};
		breaker.break_time2 = add_clocks(breaker.break_time2,Clock);
		breaker.break_time2 = add_clocks(breaker.break_time2,temp_clock2);
		breaker.break_duration2.hour = 0;
		breaker.break_duration2.minute = (*random2 % 5);
		breaker.break_duration2.second = (*random2 % 60);
	}
	if(breaker.start_break[3] == 1){
		breaker.start_break[3] = 0;
		HAL_RNG_GenerateRandomNumber(&hrng,random3);
		WallClock temp_clock2 = { .hour = 0, .minute = (30 + (*random3 - 30) % 31), .second = (*random3 % 60)};
		breaker.break_time3 = add_clocks(breaker.break_time3,Clock);
		breaker.break_time3 = add_clocks(breaker.break_time3,temp_clock2);
		breaker.break_duration3.hour = 0;
		breaker.break_duration3.minute = (*random2 % 5);
		breaker.break_duration3.second = (*random2 % 60);
	}

}

//TODO Implement manual function for the buttons for breaks
