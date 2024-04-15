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
#include "cmsis_os.h"

int num[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0X80, 0X90};
int seg[] = {0xF1, 0xF2, 0xF4, 0xF8};

int updateDigit(int spot, int num){
	if (spot == 0){
		return num / 1000;
	} else if (spot == 1){
		return (num / 100) % 10;
	} else if (spot == 2){
		return (num / 10) % 10;
	} else {
		return num % 10;
	}
}

void run_manager(){
//	if((Clock.minute % 2) == 0 && (Clock.second % 60) == 30){
//			sprintf(buffer, "Current time: %d:%d:%d \r\n", Clock.hour, Clock.minute, Clock.second);
//			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
//			sprintf(buffer,"Customers waiting in Queue: %d \r\n", waiting_customers);
//			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
//			sprintf(buffer,"Teller 1: %d Teller 2: %d Teller 3: %d \r\n", tellers[1].status,tellers[2].status,tellers[3].status);
//			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
//		}

	if (clock_compare(Clock, fiveOclockSomewhere) == 0 && waiting_customers == 0 && tellers[0].status == 0 && tellers[1].status == 0 && tellers[2].status == 0){
		day_over = 1;

		// Base stats for everyone
		int total_customers = 0;
		int total_teller_waits = 0;
		WallClock total_service_time = {.hour = 0, .minute = 0, .second = 0};
		WallClock total_t_waiting_time = {.hour = 0, .minute = 0, .second = 0};

		// Individual Teller Stats
		for (int i = 0; i < 3; i++){

			total_customers += tellers[i].customers_served;
			total_teller_waits += tellers[i].waiting_count;
			total_service_time = add_clocks(total_service_time, tellers[i].total_time_working);
			total_t_waiting_time = add_clocks(total_t_waiting_time, tellers[i].total_time_waiting);
//			char buffer[100];
//					sprintf(buffer, "Current time: %d:%d:%d \r\n", total_t_waiting_time.hour, total_t_waiting_time.minute, total_t_waiting_time.second);
//					HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		}

		// Everyone stats calculated
		WallClock avg_wait_time_customer = average_time(total_customer_wait, total_customers);
		WallClock avg_time_with_teller = average_time(total_service_time, total_customers);
		WallClock avg_wait_time_teller = average_time(total_t_waiting_time, total_teller_waits);
		//WallClock max_queue_time = {.hour = 0, .minute = 0, .second = 0};
//		char buffer[100];
//		sprintf(buffer, "Customer wait time: %d:%d:%d \r\n", total_customer_wait.hour, total_customer_wait.minute, total_customer_wait.second);
//		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);

		char buffer[256];
		sprintf(buffer, "\r\n-------------------- End of Day Report ---------------------\r\n");
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Customers serviced: %d\r\n", total_customers);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Customers serviced by Teller 1: %d\r\n", tellers[0].customers_served);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Customers serviced by Teller 2: %d\r\n", tellers[1].customers_served);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Customers serviced by Teller 3: %d\r\n\r\n", tellers[2].customers_served);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);

		sprintf(buffer, "Average customer wait time: %d:%d:%d\r\n", avg_wait_time_customer.hour, avg_wait_time_customer.minute, avg_wait_time_customer.second);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Average customer time with Tellers: %d:%d:%d\r\n", avg_time_with_teller.hour, avg_time_with_teller.minute, avg_time_with_teller.second);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Average teller wait time: %d:%d:%d\r\n", avg_wait_time_teller.hour, avg_wait_time_teller.minute, avg_wait_time_teller.second);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		sprintf(buffer, "Max customers in queue: %d\r\n\r\n", max_customer_waiting);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);

		for (int i = 0; i < 3; i++){
			sprintf(buffer, "Number of breaks for Teller %d: %d\r\n", i, tellers[i].num_breaks);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
			WallClock avg_break = average_time(tellers[i].total_break, tellers[i].num_breaks);
			sprintf(buffer, "Average break time for Teller %d: %d:%d:%d\r\n", i, avg_break.hour, avg_break.minute, avg_break.second); //calculate avg
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
			sprintf(buffer, "Max break time for Teller %d: %d:%d:%d\r\n", i, tellers[i].max_break.hour, tellers[i].max_break.minute, tellers[i].max_break.second);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
			sprintf(buffer, "Min break time for Teller %d: %d:%d:%d\r\n\r\n", i, tellers[i].min_break.hour, tellers[i].min_break.minute, tellers[i].min_break.second);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		}
	}

	for (int i = 0; i < 4; i++){
			int digit = updateDigit(i, waiting_customers);
			HAL_GPIO_WritePin(SHLD_D4_SEG7_Latch_GPIO_Port, SHLD_D4_SEG7_Latch_Pin, GPIO_PIN_RESET);
			shiftOut(SHLD_D8_SEG7_Data_GPIO_Port, SHLD_D8_SEG7_Data_Pin, SHLD_D7_SEG7_Clock_GPIO_Port, SHLD_D7_SEG7_Clock_Pin, num[digit]);
			shiftOut(SHLD_D8_SEG7_Data_GPIO_Port, SHLD_D8_SEG7_Data_Pin, SHLD_D7_SEG7_Clock_GPIO_Port, SHLD_D7_SEG7_Clock_Pin, seg[i]);
			HAL_GPIO_WritePin(SHLD_D4_SEG7_Latch_GPIO_Port, SHLD_D4_SEG7_Latch_Pin, GPIO_PIN_SET);
		}
}



void shiftOut(GPIO_TypeDef* data_port, uint16_t data_pin, GPIO_TypeDef* clock_port, uint16_t clock_pin, uint8_t value) {
	for(int ii=0x80; ii; ii>>=1) {
		HAL_GPIO_WritePin(clock_port, clock_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(data_port, data_pin, (value&ii)!=0);
		HAL_GPIO_WritePin(clock_port, clock_pin, GPIO_PIN_SET);
	}
}
