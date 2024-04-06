/*
 * led.c
 *
 *  Created on: April 5, 2024
 *      Author: Beekman
 */

#include "stm32l476xx.h"
#include "main.h"
#include "clock.h"

Teller tellers[3];

void initialize_tellers(void) {
    for (int i = 1; i < 4; i++) {
    	//Initialize ID
        tellers[i].id = i;
        // Initialize statuses
        tellers[i].status = 0;
        tellers[i].take_break = 0;
        //service function
        clock_init(tellers[i].service_end_time);
        //Initialize metrics
        tellers[i].customers_served = 0;
        clock_init(tellers[i].total_time_working);
        clock_init(tellers[i].total_time_waiting);
        clock_init(tellers[i].current_time_working);
        clock_init(tellers[i].current_time_waiting);
        clock_init(tellers[i].max_time_working);
        clock_init(tellers[i].max_time_waiting);
        //Initialize break taking
        clock_init(tellers[i].break_end);
        clock_init(tellers[i].current_break);
        //Initialize break metrics
        tellers[i].num_breaks = 0;
        clock_init(tellers[i].max_break);
        clock_init(tellers[i].min_break);
        clock_init(tellers[i].total_break);

    }
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
			if(clock_compare(tellers[i].current_break,tellers[i].break_end) != 1){
				//go onto next teller
				clock_increment(tellers[i].current_break);
				break;
			}
			//If teller is on break and it is over
			if(clock_compare(tellers[i].current_break,tellers[i].break_end) == 1){
				if(clock_compare(tellers[i].current_break,tellers[i].max_break) == 0){
					tellers[i].max_break = tellers[i].current_break;
				}
				if(clock_compare(tellers[i].current_break,tellers[i].min_break) == 2){
					tellers[i].min_break = tellers[i].current_break;
				}
				add_clocks(tellers[i].total_break, tellers[i].current_break);
				clock_init(tellers[i].current_break);
				tellers[i].status = 0;
				//HAVE TELLER ENTER THE QUEUE IF NOT ALREADY IN IT
				break;
			}
			//Case Break
			break;
		//Teller Currently Waiting
		case 0:
			//If teller is waiting and doesn't need to go on break;
			if(tellers[i].take_break == 0){
				clock_increment(tellers[i].current_time_waiting);
				break;
			}
			//If teller is waiting and needs to go on break
			if(tellers[i].take_break == 1){
				tellers[i].status = 2;
				switch (i){
				case 1:
					//Do with initialized Breaker in Breakers.C
					break;
				case 2:
					//Do with initialized Breaker in Breakers.C
					break;
				case 3:
					//Do with initialized Breaker in Breakers.C
					break;
				default:
					break;
				}
				tellers[i].take_break = 0;
				if(clock_compare(tellers[i].current_time_waiting,tellers[i].max_time_waiting) == 0){
					tellers[i].max_time_waiting = tellers[i].current_time_waiting;
				}
				add_clocks(tellers[i].total_time_waiting,tellers[i].current_time_waiting);
				clock_init(tellers[i].current_time_waiting);
			}
			//Case Break
			break;
		//Teller currently Servicing
		case 1:
			//If teller is servicing and not finished
			if(clock_compare(tellers[i].current_time_working,tellers[i].service_end_time) == 1){
				clock_increment(tellers[i].current_time_working);
				break;
			}
			//If teller is servicing and finished
			if(clock_compare(tellers[i].current_time_working,tellers[i].service_end_time) == 1){
				if(clock_compare(tellers[i].current_time_working,tellers[i].max_time_working) == 0){
					tellers[i].max_time_working = tellers[i].current_time_working;
				}
				add_clocks(tellers[i].total_time_working,tellers[i].current_time_working);
				clock_init(tellers[i].current_time_working);
				tellers[i].status = 0;
				//ADD THEM TO QUEUE
				break;
			}
		}
			//Case Break
			break;
	}
}

//Grab Customers from customer queue function. Sets end_service time.
//If Teller is waiting,
//pop them out and have them not get back into queue until they are done


