/*
 * customer.c
 *
 *  Created on: Apr 2, 2024
 *      Author: alex3
 */

#include "clock.h"
#include "customer.h"
#include "main.h"

int max_customer_waiting;
int waiting_customers;
Customer* waiting[100];
WallClock *new_customer_time;
uint32_t* random_service_time;
uint32_t* random_new_customer;
Customer* c;
WallClock total_customer_wait;
WallClock max_customer_wait;
int total_customers;
WallClock fiveOclockSomewhere = {.hour = 17, .minute = 0, .second = 0};

void init_customer(){
	total_customers = 0;
	total_customer_wait = clock_init(total_customer_wait);
	max_customer_waiting = 0;
	max_customer_wait = clock_init(max_customer_wait);
	waiting_customers = 0;
	HAL_RNG_GenerateRandomNumber(&hrng, random_new_customer);
	new_customer_time->hour = 0;
	new_customer_time->minute = (*random_new_customer % 5);
	new_customer_time->second = (*random_new_customer % 60);
	*new_customer_time = add_clocks(*new_customer_time, Clock);
}


void run_customer(){
	// shift customers if first customers want to
	if((waiting[0] == NULL) && waiting[1] != NULL){
		for (int i = 0; i < waiting_customers; i++){
			waiting[i] = waiting[i+1];
		}
		waiting_customers--;
	}

	for (int i = 0; i < waiting_customers; i++){
		waiting[i]->total_queue_time = clock_increment(waiting[i]->total_queue_time);
	}

	// add new customer if enough time has passed
	if (clock_compare(Clock, *new_customer_time) == 1 && clock_compare(Clock, fiveOclockSomewhere) == 2){
		HAL_RNG_GenerateRandomNumber(&hrng, random_service_time);
		WallClock service_time = { .hour = 0, .minute = (*random_service_time % 7), .second = (*random_service_time % 60)};
		c->service_time = service_time;
		c->entered_queue_time = Clock;
		c->total_queue_time = (WallClock) {.hour = 0, .minute = 0, .second = 0};
		waiting[waiting_customers] = c;
		HAL_RNG_GenerateRandomNumber(&hrng, random_new_customer);
		new_customer_time->hour = 0;
		new_customer_time->minute = (*random_new_customer % 5);
		new_customer_time->second = (*random_new_customer % 60);
		*new_customer_time = add_clocks(*new_customer_time, Clock);
		total_customers += 1;
	}

	// update max customers waiting
	if (max_customer_waiting < waiting_customers){
		max_customer_waiting = waiting_customers;
	}


}


