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

void init_customer(){
	max_customer_waiting = 0;
	waiting_customers = 0;
	HAL_RNG_GenerateRandomNumber(&hrng, random_new_customer);
	new_customer_time->hour = 0;
	new_customer_time->minute = (30 + (*random_new_customer - 30) % 31);
	new_customer_time->second = (*random_new_customer % 60);
	add_clocks(*new_customer_time, Clock);
}


void run_customer(){
	// shift customers if first customers want to
	if (waiting[0] == NULL){
		for (int i = 0; i < waiting_customers; i++){
			waiting[i] = waiting[i+1];
		}
		waiting_customers--;
	}

	// add new customer if enough time has passed
	if (clock_compare(Clock, *new_customer_time) == 1){
		HAL_RNG_GenerateRandomNumber(&hrng, random_service_time);
		WallClock service_time = { .hour = 0, .minute = (30 + (*random_service_time - 30) % 31), .second = (*random_service_time % 60)};
		c->service_time = service_time;
		c->entered_queue_time = Clock;
		waiting[waiting_customers] = c;
		HAL_RNG_GenerateRandomNumber(&hrng, random_new_customer);
		new_customer_time->hour = 0;
		new_customer_time->minute = (30 + (*random_new_customer - 30) % 31);
		new_customer_time->second = (*random_new_customer % 60);
		add_clocks(*new_customer_time, Clock);
	}

	// update max customers waiting
	if (max_customer_waiting < waiting_customers){
		max_customer_waiting = waiting_customers;
	}
}


