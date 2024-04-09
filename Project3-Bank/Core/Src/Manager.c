/*
 * Manager.c
 *
 *  Created on: Apr 7, 2024
 *      Author: alex3
 */


#include "main.h"
#include "customer.h"
#include "clock.h"
#include "teller.h"
#include "stdio.h"
#include "string.h"

void run_manager(){
	if (clock_compare(Clock, fiveOclockSomewhere) == 1 && waiting_customers == 0){
		// Everyone stats
		int total_customers = 0;
		WallClock total_service_time = {.hour = 0, .minute = 0, .second = 0};
		WallClock avg_wait_time_customer = {.hour = 0, .minute = 0, .second = 0};
		WallClock avg_time_with_teller = {.hour = 0, .minute = 0, .second = 0};
		WallClock avg_wait_time_teller = {.hour = 0, .minute = 0, .second = 0};
		//WallClock max_queue_time = {.hour = 0, .minute = 0, .second = 0};
		// Individual Teller stats
		for (int i = 1; i < 4; i++){
			total_customers += tellers[i].customers_served;
			total_service_time = add_clocks(total_service_time, tellers[i].total_time_working);
		}

		char buffer[256];
		sprintf(buffer, "\r\n-------------------- End of Day Report ---------------------\r\n");
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Customers serviced: %d\r\n", total_customers);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Customers serviced by Teller 1: %d\r\n", tellers[1].customers_served);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Customers serviced by Teller 2: %d\r\n", tellers[2].customers_served);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Customers serviced by Teller 3: %d\r\n", tellers[3].customers_served);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);

		sprintf(buffer, "Average customer wait time: %d:%d:%d\r\n", avg_wait_time_customer.hour, avg_wait_time_customer.minute, avg_wait_time_customer.second);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Average customer time with Tellers: %d:%d:%d\r\n", avg_time_with_teller.hour, avg_time_with_teller.minute, avg_time_with_teller.second);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Average teller wait time: %d:%d:%d\r\n", avg_wait_time_teller.hour, avg_wait_time_teller.minute, avg_wait_time_teller.second);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Max customers in queue: %d\r\n", max_customer_waiting);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);

		for (int i = 1; i < 4; i++){
			sprintf(buffer, "Number of breaks for Teller %d: %d\r\n", i, tellers[i].num_breaks);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
			sprintf(buffer, "Average break time for Teller %d: %d:%d:%d\r\n", i, tellers[i].current_break.hour, tellers[i].current_break.minute, tellers[i].current_break.second); //calculate avg
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
			sprintf(buffer, "Max break time for Teller %d: %d:%d:%d\r\n", i, tellers[i].max_break.hour, tellers[i].max_break.minute, tellers[i].max_break.second);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
			sprintf(buffer, "Min break time for Teller %d: %d:%d:%d\r\n", i, tellers[i].min_break.hour, tellers[i].min_break.minute, tellers[i].min_break.second);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		}
	}
}
