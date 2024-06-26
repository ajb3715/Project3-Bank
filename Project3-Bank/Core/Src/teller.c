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

Teller tellers[4];

Teller VOID_TELLER;
//fix this
Teller teller_wait[4];

void initialize_tellers(void) {
    for (int i = 1; i < 4; i++) {
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

        //initialize tellers in Queue
        teller_wait[i-1] = tellers[i];

    }
    	teller_wait[0] = VOID_TELLER;
}

//Maybe Put entire thing inside a case statement if at all possible,
//Would Simplify logic and speed it up
void manage_tellers(void){
	int i;
	for (i = 1; i < 4; i++) {
		switch (tellers[i].status){
		//Teller Currently Breaking
		case 2:
			//If teller is on break and it isn't over
			if(clock_compare(Clock,tellers[i].break_end) != 1){
				//go onto next teller
				break;
			}
			//If teller is on break and it is over
			if(clock_compare(Clock,tellers[i].break_end) == 1){
				if(clock_compare(tellers[i].current_break,tellers[i].max_break) == 0){
					tellers[i].max_break = tellers[i].current_break;
				}
				if(clock_compare(tellers[i].current_break,tellers[i].min_break) == 2){
					tellers[i].min_break = tellers[i].current_break;
				}
				tellers[i].total_break = add_clocks(tellers[i].total_break, tellers[i].current_break);
				tellers[i].current_break = clock_init(tellers[i].current_break);
				tellers[i].status = 0;
				//HAVE TELLER ENTER THE QUEUE IF NOT ALREADY IN IT
				if(!((teller_wait[0].id == i) && (teller_wait[1].id == i) && (teller_wait[2].id == i))){
					if(teller_wait[0].id == 0){
						teller_wait[0] = tellers[i];
					}
					else if(teller_wait[1].id == 0){
						teller_wait[1] = tellers[i];
					}
					else if(teller_wait[2].id == 0){
						teller_wait[2] = tellers[i];
					}
					break;
				}
				tellers[i].teller_start_wait = Clock;
			}
			//Case Break
			break;
		//Teller Currently Waiting
		case 0:
			//If teller is waiting and doesn't need to go on break;
			if(tellers[i].take_break == 0){
				//Check to see if they can grab a customer

				//Check to see if the queue is not empty, and this teller is at the front of the queue

				  if((waiting[0] != NULL) && (tellers[i].id == teller_wait[0].id)){
					tellers[i].current_time_waiting = subtract_Clocks(Clock,tellers[i].teller_start_wait);
					Customer customer = *waiting[0];
					waiting[0] = NULL;
//				  	//TODO
				  	tellers[i].service_end_time = customer.service_time;
//				  	update any needed metric stuff for the customer shit TODO
				  	total_customer_wait = add_clocks(total_customer_wait, customer.total_queue_time);
				  	if(clock_compare(customer.total_queue_time,max_customer_wait) == 0){
				  		max_customer_wait = customer.total_queue_time;
				  	}
				  	tellers[i].status = 1;
				  	if(clock_compare(tellers[i].current_time_waiting,tellers[i].max_time_waiting) == 0){
				 	tellers[i].max_time_waiting = tellers[i].current_time_waiting;
				 	teller_wait[0] = teller_wait[1];
				 	teller_wait[1] = teller_wait[2];
				 	teller_wait[3] = teller_wait[3];
				 	teller_wait[4] = VOID_TELLER;
				 	}
				  	tellers[i].current_time_waiting = clock_init(tellers[i].current_time_waiting);
				  }

				break;
			}
			//If teller is waiting and needs to go on break
			if(tellers[i].take_break == 1){

				tellers[i].status = 2;
				switch (i){
				case 1:
					//Do with initialized Breaker in Breakers.C
					breaker.start_break[i] = 1;
					tellers[i].break_end = breaker.break_duration1;
					tellers[i].current_break = breaker.break_duration1;
					breaker.break_duration1 = clock_init(breaker.break_duration1);
					breaker.break_time1 = clock_init(breaker.break_time1);
					tellers[i].break_end = add_clocks(Clock, tellers[i].break_end);
					break;
				case 2:
					//Do with initialized Breaker in Breakers.C
					breaker.start_break[i] = 1;
					tellers[i].break_end = breaker.break_duration2;
					tellers[i].current_break = breaker.break_duration2;
					breaker.break_duration2 = clock_init(breaker.break_duration2);
					breaker.break_time2 = clock_init(breaker.break_time2);
					tellers[i].break_end = add_clocks(Clock, tellers[i].break_end);
					break;
				case 3:
					//Do with initialized Breaker in Breakers.C
					breaker.start_break[i] = 1;
					tellers[i].break_end = breaker.break_duration3;
					tellers[i].current_break = breaker.break_duration3;
					breaker.break_duration3 = clock_init(breaker.break_duration3);
					breaker.break_time3 = clock_init(breaker.break_time3);
					tellers[i].break_end = add_clocks(Clock, tellers[i].break_end);
					break;
				default:
					break;
				}
				tellers[i].take_break = 0;
				if(clock_compare(tellers[i].current_time_waiting,tellers[i].max_time_waiting) == 0){
					tellers[i].max_time_waiting = tellers[i].current_time_waiting;
				}
				tellers[i].total_time_waiting = add_clocks(tellers[i].total_time_waiting,tellers[i].current_time_waiting);
				tellers[i].current_time_waiting = clock_init(tellers[i].current_time_waiting);
			}
			//Case Break
			break;
		//Teller currently Servicing
		case 1:
			//If teller is servicing and not finished
			if(clock_compare(tellers[i].current_time_working,tellers[i].service_end_time) == 1){
				tellers[i].current_time_working = clock_increment(tellers[i].current_time_working);
				break;
			}
			//If teller is servicing and finished
			if(clock_compare(tellers[i].current_time_working,tellers[i].service_end_time) == 1){
				if(clock_compare(tellers[i].current_time_working,tellers[i].max_time_working) == 0){
					tellers[i].max_time_working = tellers[i].current_time_working;
				}
				tellers[i].total_time_working = add_clocks(tellers[i].total_time_working,tellers[i].current_time_working);
				tellers[i].current_time_working = clock_init(tellers[i].current_time_working);
				tellers[i].status = 0;
				tellers[i].teller_start_wait = Clock;
				//Have Teller RE-Enter Queue
				if(!((teller_wait[0].id == i) && (teller_wait[1].id == i) && (teller_wait[2].id == i))){
					if(teller_wait[0].id == 0){
						teller_wait[0] = tellers[i];
					}
					else if(teller_wait[1].id == 0){
						teller_wait[1] = tellers[i];
					}
					else if(teller_wait[2].id == 0){
						teller_wait[2] = tellers[i];
					}
					break;
				}
				break;
			}
		}
			//Case Break
			break;
	}

}




