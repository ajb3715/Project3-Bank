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
extern WallClock max_customer_wait;
extern WallClock fiveOclockSomewhere;
extern int max_customer_waiting;
extern int total_customers;

#define SHLD_D7_SEG7_Clock_Pin GPIO_PIN_8
#define SHLD_D7_SEG7_Clock_GPIO_Port GPIOA
#define SHLD_D8_SEG7_Data_Pin GPIO_PIN_9
#define SHLD_D8_SEG7_Data_GPIO_Port GPIOA
#define SHLD_D4_SEG7_Latch_Pin GPIO_PIN_4
#define SHLD_D4_SEG7_Latch_GPIO_Port GPIOB
#define SHLD_D13_Pin GPIO_PIN_5
#define SHLD_D13_GPIO_Port GPIOA
#define SHLD_D12_Pin GPIO_PIN_6
#define SHLD_D12_GPIO_Port GPIOA
#define SHLD_D11_Pin GPIO_PIN_7
#define SHLD_D11_GPIO_Port GPIOA

void init_customer();
void run_customer();
void shiftOut(GPIO_TypeDef* data_port, uint16_t data_pin, GPIO_TypeDef* clock_port, uint16_t clock_pin, uint8_t value);

#endif /* INC_CUSTOMER_H_ */
