/*
 * customer.h
 *
 *  Created on: Apr 2, 2024
 *      Author: alex3
 */

#ifndef INC_CUSTOMER_H_
#define INC_CUSTOMER_H_

extern int waiting_customers;
extern Customer* waiting[100];
extern WallClock total_customer_wait;
extern int total_customers;

void init_customer();
void run_customer();

#endif /* INC_CUSTOMER_H_ */
