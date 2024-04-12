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

		}


		//case break
		break;
	//Teller Currently Servicing
	case 1:

		//case break
		break;

	}
}



