/*
 * customer.c
 *
 *  Created on: Apr 2, 2024
 *      Author: alex3
 */


#include "customer.h"
#include "main.h"

int customer_count;
int waiting_customers;
Customer* waiting[100];

void init_customer(){
	customer_count = 0;
	waiting_customers = 0;
}


void run_customer(){
	if (waiting[0] == NULL){
		for (int i = 0; i < waiting_customers; i++){
			// shift customers forward
		}
		waiting_customers--;
	}

	for (int i = 0; i < waiting_customers; i++){
		// increment wait time for each customer waiting

	}

	// add new customer if enough time has passed

}


