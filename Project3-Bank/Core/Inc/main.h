/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define Switch1_Pin GPIO_PIN_1
#define Switch1_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define Switch2_Pin GPIO_PIN_4
#define Switch2_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define Switch3_Pin GPIO_PIN_0
#define Switch3_GPIO_Port GPIOB
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern RNG_HandleTypeDef hrng;
extern UART_HandleTypeDef huart2;
extern int update_flag;

typedef struct {
    int hour;
    int minute;
    int second;
} WallClock;

typedef struct {
	//identification
	int id;
	int status; // 0 is waiting, 1 is servicing, 2 is breaking
	int take_break; // 0 is don't take break, 1 is break needs to be taken

	//service function
	WallClock service_end_time;

	//metrics
	int customers_served;
	WallClock total_time_working;
	WallClock total_time_waiting;

	WallClock current_time_working;
	WallClock current_time_waiting;

	WallClock max_time_working;
	WallClock max_time_waiting;

	//break functions
	WallClock break_end;
	//Tracks how long the current break is;
	WallClock current_break;

	//break metrics
	//AVG break will be calculated using the time on break divided by num break

	int num_breaks;
	WallClock max_break;
	WallClock min_break;
	WallClock total_break;


} Teller;

typedef struct {
	//The breaker should
	//First teller
	int start_break[3];
	WallClock break_time1;
	WallClock break_duration1;
	//First teller

	WallClock break_time2;
	WallClock break_duration2;
	//First teller

	WallClock break_time3;
	WallClock break_duration3;

} Breaker;

typedef struct {
	// ID which also acts as a check for customer count
	int id;

	// Information for tellers (
	WallClock service_time;

	//Metric Tracking
	WallClock entered_queue_time;
	WallClock left_queue_time;
	WallClock total_queue_time;

} Customer;


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
