/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "clock.h"
#include "customer.h"
#include "teller.h"
#include "breaker.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "manager.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RNG_HandleTypeDef hrng;

TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

/* Definitions for Teller0 */
osThreadId_t Teller0Handle;
const osThreadAttr_t Teller0_attributes = {
  .name = "Teller0",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Customers */
osThreadId_t CustomersHandle;
const osThreadAttr_t Customers_attributes = {
  .name = "Customers",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Clock */
osThreadId_t ClockHandle;
const osThreadAttr_t Clock_attributes = {
  .name = "Clock",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Manager */
osThreadId_t ManagerHandle;
const osThreadAttr_t Manager_attributes = {
  .name = "Manager",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Breaker */
osThreadId_t BreakerHandle;
const osThreadAttr_t Breaker_attributes = {
  .name = "Breaker",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Teller1 */
osThreadId_t Teller1Handle;
const osThreadAttr_t Teller1_attributes = {
  .name = "Teller1",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Teller2 */
osThreadId_t Teller2Handle;
const osThreadAttr_t Teller2_attributes = {
  .name = "Teller2",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for MUTEX */
osMutexId_t MUTEXHandle;
const osMutexAttr_t MUTEX_attributes = {
  .name = "MUTEX",
  .attr_bits = osMutexRecursive,
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_RNG_Init(void);
static void MX_TIM6_Init(void);
void StartTeller0(void *argument);
void StartCustomers(void *argument);
void StartClock(void *argument);
void StartManager(void *argument);
void StartBreaker(void *argument);
void StartTeller1(void *argument);
void StartTeller2(void *argument);

/* USER CODE BEGIN PFP */
int update_flag = 0;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */


  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_RNG_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim6);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* Create the recursive mutex(es) */
  /* creation of MUTEX */
  MUTEXHandle = osMutexNew(&MUTEX_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Teller0 */
  Teller0Handle = osThreadNew(StartTeller0, NULL, &Teller0_attributes);

  /* creation of Customers */
  CustomersHandle = osThreadNew(StartCustomers, NULL, &Customers_attributes);

  /* creation of Clock */
  ClockHandle = osThreadNew(StartClock, NULL, &Clock_attributes);

  /* creation of Manager */
  ManagerHandle = osThreadNew(StartManager, NULL, &Manager_attributes);

  /* creation of Breaker */
  BreakerHandle = osThreadNew(StartBreaker, NULL, &Breaker_attributes);

  /* creation of Teller1 */
  Teller1Handle = osThreadNew(StartTeller1, NULL, &Teller1_attributes);

  /* creation of Teller2 */
  Teller2Handle = osThreadNew(StartTeller2, NULL, &Teller2_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 8;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 224;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 Switch1_Pin Switch2_Pin PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|Switch1_Pin|Switch2_Pin|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Switch3_Pin PB10 PB4 */
  GPIO_InitStruct.Pin = Switch3_Pin|GPIO_PIN_10|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	update_flag = 1;
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartTeller0 */
/**
  * @brief  Function implementing the Teller0 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTeller0 */
void StartTeller0(void *argument)
{
  /* USER CODE BEGIN 5 */
	//Initialize 3 tellers
  /* Infinite loop */
	init_teller(0);
  for(;;)
  {
		osMutexAcquire(MUTEXHandle, osWaitForever);
		manage_teller(0);
		osMutexRelease(MUTEXHandle);
  }
  osThreadYield();
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartCustomers */
/**
* @brief Function implementing the Customers thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCustomers */
void StartCustomers(void *argument)
{
  /* USER CODE BEGIN StartCustomers */
  /* Infinite loop */
  init_customer();
  for(;;)
  {

	osMutexAcquire(MUTEXHandle, osWaitForever);
	run_customer();
	osMutexRelease(MUTEXHandle);


  }
  osThreadYield();
  /* USER CODE END StartCustomers */
}

/* USER CODE BEGIN Header_StartClock */
/**
* @brief Function implementing the Clock thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartClock */
void StartClock(void *argument)
{
  /* USER CODE BEGIN StartClock */
  /* Infinite loop */
	Clock = day_init(Clock);
  for(;;)
  {
	if(update_flag == 1){
	osMutexAcquire(MUTEXHandle, osWaitForever);
    Clock = clock_increment(Clock);
    char buffer[256];
	if((Clock.minute  % 2) == 0 && (Clock.second % 60) == 30){
			sprintf(buffer, "Current time: %d:%d:%d \r\n", Clock.hour, Clock.minute, Clock.second);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
			sprintf(buffer,"Customers waiting in Queue: %d \r\n", waiting_customers );
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
			sprintf(buffer,"Teller 1: %d Teller 2: %d Teller 3: %d \r\n", tellers[1].status,tellers[2].status,tellers[3].status);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
		}
    osMutexRelease(MUTEXHandle);
	}
	update_flag = 0;
  }
  /* USER CODE END StartClock */
}

/* USER CODE BEGIN Header_StartManager */
/**
* @brief Function implementing the Manager thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartManager */
void StartManager(void *argument)
{
  /* USER CODE BEGIN StartManager */
  /* Infinite loop */
  for(;;)
  {
	  osMutexAcquire(MUTEXHandle, osWaitForever);
	  run_manager();
	  osMutexRelease(MUTEXHandle);

  }
  osThreadYield();
  /* USER CODE END StartManager */
}

/* USER CODE BEGIN Header_StartBreaker */
/**
* @brief Function implementing the Breaker thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBreaker */
void StartBreaker(void *argument)
{
  /* USER CODE BEGIN StartBreaker */
  /* Infinite loop */
	init_breaker();
  for(;;)
  {
	osMutexAcquire(MUTEXHandle, osWaitForever);
	run_breaker();
	osMutexRelease(MUTEXHandle);

  }
  osThreadYield();
  /* USER CODE END StartBreaker */
}

/* USER CODE BEGIN Header_StartTeller1 */
/**
* @brief Function implementing the Teller1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTeller1 */
void StartTeller1(void *argument)
{
  /* USER CODE BEGIN StartTeller1 */
  /* Infinite loop */
	init_teller(1);
  for(;;)
  {
	osMutexAcquire(MUTEXHandle, osWaitForever);
	manage_teller(1);
	osMutexRelease(MUTEXHandle);
  }
  osThreadYield();
  /* USER CODE END StartTeller1 */
}

/* USER CODE BEGIN Header_StartTeller2 */
/**
* @brief Function implementing the Teller2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTeller2 */
void StartTeller2(void *argument)
{
  /* USER CODE BEGIN StartTeller2 */
  /* Infinite loop */
	init_teller(2);
  for(;;){
	osMutexAcquire(MUTEXHandle, osWaitForever);
	manage_teller(2);
	osMutexRelease(MUTEXHandle);
    //osDelay(1);
  }
  osThreadYield();
  /* USER CODE END StartTeller2 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
