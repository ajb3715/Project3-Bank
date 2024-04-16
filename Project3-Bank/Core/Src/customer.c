/*
 * customer.c
 *
 *  Created on: Apr 2, 2024
 *      Author: alex3
 */

#include <stdlib.h>
#include "clock.h"
#include "customer.h"
#include "main.h"
#include "cmsis_os.h"

int max_customer_waiting;
int waiting_customers;
Customer* waiting[100];
WallClock new_customer_time;

//Customer c;
WallClock total_customer_wait;
WallClock max_customer_wait;
int total_customers;
WallClock fiveOclockSomewhere = {.hour = 17, .minute = 0, .second = 0};


void init_GPIO(){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*Configure GPIO pins : SHLD_D13_Pin SHLD_D12_Pin SHLD_D11_Pin SHLD_D7_SEG7_Clock_Pin */
	GPIO_InitStruct.Pin = SHLD_D13_Pin|SHLD_D12_Pin|SHLD_D11_Pin|SHLD_D7_SEG7_Clock_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : SHLD_D8_SEG7_Data_Pin */
	GPIO_InitStruct.Pin = SHLD_D8_SEG7_Data_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(SHLD_D8_SEG7_Data_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : SHLD_D4_SEG7_Latch_Pin */
	GPIO_InitStruct.Pin = SHLD_D4_SEG7_Latch_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SHLD_D4_SEG7_Latch_GPIO_Port, &GPIO_InitStruct);
}

void init_customer(){
	uint32_t random_new_customer = 0;
	total_customers = 0;
	total_customer_wait = clock_init(total_customer_wait);
	max_customer_waiting = 0;
	max_customer_wait = clock_init(max_customer_wait);
	waiting_customers = 0;
	HAL_RNG_GenerateRandomNumber(&hrng, &random_new_customer);
	new_customer_time.hour = 0;
	new_customer_time.minute = (random_new_customer % 3) + 1;
	new_customer_time.second = (random_new_customer % 60);
	new_customer_time = add_clocks(new_customer_time, Clock);
	init_GPIO();
	HAL_GPIO_WritePin(SHLD_D4_SEG7_Latch_GPIO_Port, SHLD_D4_SEG7_Latch_Pin, GPIO_PIN_RESET);
			shiftOut(SHLD_D8_SEG7_Data_GPIO_Port, SHLD_D8_SEG7_Data_Pin, SHLD_D7_SEG7_Clock_GPIO_Port, SHLD_D7_SEG7_Clock_Pin, 0);
			shiftOut(SHLD_D8_SEG7_Data_GPIO_Port, SHLD_D8_SEG7_Data_Pin, SHLD_D7_SEG7_Clock_GPIO_Port, SHLD_D7_SEG7_Clock_Pin, 0);
			HAL_GPIO_WritePin(SHLD_D4_SEG7_Latch_GPIO_Port, SHLD_D4_SEG7_Latch_Pin, GPIO_PIN_SET);

}



void run_customer(){
	uint32_t random_service_time =0;
	uint32_t random_new_customer = 0;
	// shift customers if first customers want to
	if((waiting[0] == NULL) && waiting[1] != NULL){
		for (int i = 0; i <= waiting_customers; i++){
			waiting[i] = waiting[i+1];
		}
	}


	// add new customer if enough time has passed
	if (clock_compare(Clock, new_customer_time) == 1 && clock_compare(Clock, fiveOclockSomewhere) == 2){
		HAL_RNG_GenerateRandomNumber(&hrng, &random_service_time);
		WallClock service_time = { .hour = 0, .minute = (random_service_time % 5) + 1, .second = (random_service_time % 60)};
		Customer *c = malloc(sizeof(Customer));
		c->service_time = service_time;
		c->id = ++total_customers;
		c->entered_queue_time = Clock;
		c->total_queue_time = (WallClock) {.hour = 0, .minute = 0, .second = 0};
		waiting[waiting_customers++] = c;
		HAL_RNG_GenerateRandomNumber(&hrng, &random_new_customer);
		new_customer_time.hour = 0;
		new_customer_time.minute = (random_new_customer % 3) + 1;
		if(new_customer_time.minute == 0){
			new_customer_time.minute = 1;
		}
		new_customer_time.second = (random_new_customer % 60);
		new_customer_time = add_clocks(new_customer_time, Clock);
	}

	// update max customers waiting
	if (max_customer_waiting < waiting_customers){
		max_customer_waiting = waiting_customers;
	}



}
