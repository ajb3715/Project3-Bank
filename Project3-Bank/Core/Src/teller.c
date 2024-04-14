/*
 * teller.c
 *
 *  Created on: April 5, 2024
 *      Author: Beekman
 */

#include <clock.h>
#include "stm32l476xx.h"
#include "main.h"
#include "breaker.h"
#include "stddef.h"
#include "customer.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "cmsis_os.h"
#include "clock.h"
Teller tellers[3];

Teller VOID_TELLER;


//Pass in the teller ID
void init_teller(int i) {
    	//Initialize ID
        tellers[i].id = i;
        // Initialize statuses
        tellers[i].status = 0;
        tellers[i].take_break = 0;
        //service function
        tellers[i].service_end_time = clock_init(tellers[i].service_end_time);
        //Initialize metrics
        tellers[i].customers_served = 0;
        tellers[i].total_time_working = clock_init(tellers[i].total_time_working);
        tellers[i].total_time_waiting = clock_init(tellers[i].total_time_waiting);
        tellers[i].current_time_working = clock_init(tellers[i].current_time_working);
        tellers[i].current_time_waiting = clock_init(tellers[i].current_time_waiting);
        tellers[i].max_time_working = clock_init(tellers[i].max_time_working);
        tellers[i].max_time_working = clock_init(tellers[i].max_time_working);
        //Initialize break taking
        tellers[i].break_end = clock_init(tellers[i].break_end);
        tellers[i].current_break = clock_init(tellers[i].current_break);
        //Initialize break metrics
        tellers[i].num_breaks = 0;
        tellers[i].max_break = clock_init(tellers[i].max_break);
        tellers[i].min_break = clock_init(tellers[i].min_break);
        tellers[i].total_break = clock_init(tellers[i].total_break);
}

//Pass in Teller ID
void manage_teller(int i){
	switch (tellers[i].status){
	//Teller Currently Breaking
	case 2:

		//case break
		break;
	//Teller is Currently Waiting
	case 0:
		//It's time to go on break
		if(breaker.start_break[i] == 1){
			tellers[i].status = 2;
			tellers[i].break_start = Clock;
			tellers[i].break_end = add_clocks(Clock, breaker.break_duration[i]);
			//Now do metrics for ending the waiting period
			tellers[i].current_time_waiting = subtract_Clocks(Clock, tellers[i].teller_start_wait);
			tellers[i].total_time_waiting = add_clocks(tellers[i].total_time_waiting,tellers[i].current_time_waiting);
			if(clock_compare(tellers[i].current_time_waiting, tellers[i].max_time_waiting) == 0){
				tellers[i].max_time_waiting = tellers[i].current_time_waiting;
			}

		}
		//It's not time to go on break, see if there is a customer waiting
		else if(waiting[0] != NULL){
			//If there is a front customer, grab him
			Customer grabbed_customer = *waiting[0];
			tellers[i].service_end_time = grabbed_customer.service_time;
			//Do metrics for the customer that was waiting
			grabbed_customer.total_queue_time = subtract_Clocks(Clock, grabbed_customer.entered_queue_time);
			total_customer_wait = add_clocks(total_customer_wait, grabbed_customer.total_queue_time);
			if(clock_compare(grabbed_customer.total_queue_time, max_customer_wait) == 0){
				max_customer_wait = grabbed_customer.total_queue_time;
			}

			//Now erase the first customer
			waiting[0] = NULL;

			//Now do metrics for ending the waiting period
			tellers[i].current_time_waiting = subtract_Clocks(Clock, tellers[i].teller_start_wait);
			tellers[i].total_time_waiting = add_clocks(tellers[i].total_time_waiting,tellers[i].current_time_waiting);
			if(clock_compare(tellers[i].current_time_waiting, tellers[i].max_time_waiting) == 0){
				tellers[i].max_time_waiting = tellers[i].current_time_waiting;
		}

		//otherwise, just keep on waiting

		//case break
		break;
	//Teller Currently Servicing
	case 1:

		//case break
		break;

	}

}



