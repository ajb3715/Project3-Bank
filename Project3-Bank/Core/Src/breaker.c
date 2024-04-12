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
	uint32_t random1 = 0;
	uint32_t random2 = 0;
	uint32_t random3 = 0;

	//What time the variable for going on break will be assigned

	breaker.start_break[0] = 0;
	//Duration of the assigned break;
	HAL_RNG_GenerateRandomNumber(&hrng,&random1);
	WallClock temp_clock1 = { .hour = 9, .minute = (30 + (random1 - 30) % 31), .second = (random1 % 60)};
	WallClock temp_clock11 = { .hour = 0, .minute = (random1 % 5), .second = (random1 % 60)};
	breaker.break_time[0] = add_clocks(breaker.break_time[0],temp_clock1);
	breaker.break_duration[0] = add_clocks(breaker.break_duration[0],temp_clock11);

	//What time the variable for going on break will be assigned
	breaker.start_break[1] = 0;
	//Duration of the assigned break;
	HAL_RNG_GenerateRandomNumber(&hrng,&random2);
	WallClock temp_clock2 = { .hour = 9, .minute = (30 + (random2 - 30) % 31), .second = (random2 % 60)};
	WallClock temp_clock22 = { .hour = 0, .minute = (random2 % 5), .second = (random2 % 60)};
	breaker.break_time[1] = add_clocks(breaker.break_time[1],temp_clock2);
	breaker.break_duration[1] = add_clocks(breaker.break_duration[1],temp_clock22);
	//What time the variable for going on break will be assigned
	breaker.start_break[2] = 0;
	//Duration of the assigned break;
	HAL_RNG_GenerateRandomNumber(&hrng,&random3);
	WallClock temp_clock3 = { .hour = 9, .minute = (30 + (random3 - 30) % 31), .second = (random3 % 60)};
	WallClock temp_clock33 = { .hour = 0, .minute = (random3 % 5), .second = (random3 % 60)};
	breaker.break_time[2] = add_clocks(breaker.break_time[2],temp_clock3);
	breaker.break_duration[2] =  add_clocks(breaker.break_duration[2],temp_clock33);
}

void run_breaker(){

	//Override automatic break if switch gets pressed
	if(((!HAL_GPIO_ReadPin(Switch1_GPIO_Port, Switch1_Pin)) == 1 ) || (clock_compare(breaker.break_time[0],Clock) == 1)){
		breaker.start_break[0] = 1;
	}
	if(((!HAL_GPIO_ReadPin(Switch1_GPIO_Port, Switch1_Pin)) == 1 ) || (clock_compare(breaker.break_time[1],Clock) == 1)){
		breaker.start_break[0] = 1;
	}
	if(((!HAL_GPIO_ReadPin(Switch1_GPIO_Port, Switch1_Pin)) == 1 ) || (clock_compare(breaker.break_time[2],Clock) == 1)){
		breaker.start_break[0] = 1;
	}


}

void generate_next_break(int teller_id){
		uint32_t random = 0;


		//What time the variable for going on break will be assigned

		breaker.start_break[teller_id] = 0;
		//Duration of the assigned break;
		HAL_RNG_GenerateRandomNumber(&hrng,&random);
		WallClock temp_clock1 = { .hour = 0, .minute = (30 + (random - 30) % 31), .second = (random % 60)};
		WallClock temp_clock11 = { .hour = 0, .minute = (random % 5), .second = (random % 60)};
		//Initialize both clocks
		breaker.break_time[teller_id] = clock_init(breaker.break_time[teller_id]);
		breaker.break_duration[teller_id] = clock_init(breaker.break_duration[teller_id]);
		//Set the clocks to their proper values
		breaker.break_time[teller_id]= add_clocks(breaker.break_time[teller_id],Clock);
		breaker.break_time[teller_id] = add_clocks(breaker.break_time[teller_id],temp_clock1);
		breaker.break_duration[teller_id] = add_clocks(breaker.break_duration[teller_id],temp_clock11);


}

//TODO Implement manual function for the buttons for breaks
