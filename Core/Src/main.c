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
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ili9488.h"
#include "lvgl.h"
#include "log.h"
#include "ui.h"
#include "screen_loader.h"
#include "global_vars.h"
#include "colors.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BYTES_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565))
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static uint8_t buf1[VERTICAL_RES * HORIZONTAL_RES * BYTES_PER_PIXEL / 15];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void my_flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
  set_draw_window(area->x1, area->y1, area->x2, area->y2);
  uint16_t *buf16 = (uint16_t *)px_map;

  uint32_t width = area->x2 - area->x1 + 1;
  uint32_t height = area->y2 - area->y1 + 1;
  uint32_t pixel_count = width * height;

  // Buffer per i dati da inviare, ogni pixel avrà 3 byte (RGB)
  uint8_t v_buffer[pixel_count * 3];

  // Pre-compiliamo i dati nel buffer
  uint32_t i = 0;
  for (uint32_t j = 0; j < pixel_count; j++)
  {
    uint16_t color = *buf16++;

    // Estrazione dei componenti RGB
    uint8_t r = (color >> 8) & 0xF8; // 5 bit rosso
    uint8_t g = (color >> 3) & 0xFC; // 6 bit verde
    uint8_t b = (color << 3);        // 5 bit blu

    v_buffer[i++] = r; // Red
    v_buffer[i++] = g; // Green
    v_buffer[i++] = b; // Blue
  }

  HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);
  HAL_SPI_Transmit_DMA(&hspi2, v_buffer, pixel_count * 3);

  while (HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY)
    ;

  HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);
  lv_display_flush_ready(display);
}

void monitor_memory()
{
  lv_mem_monitor_t mem_monitor;
  lv_mem_monitor(&mem_monitor); // Ottieni i dati sulla memoria

  // Buffer per contenere il messaggio
  char buffer[128];

  // Formatta i dati di memoria
  snprintf(buffer, sizeof(buffer),
           "Memory total: %d bytes\r\n"
           "Memory free: %d bytes\r\n"
           "Memory used: %d bytes\r\n"
           "Memory fragmentation: %d%%\r\n",
           mem_monitor.total_size,
           mem_monitor.free_size,
           mem_monitor.total_size - mem_monitor.free_size,
           mem_monitor.frag_pct);

  // Trasmetti il messaggio su UART
  HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
}
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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  lcd_init_spi();

  lv_init();
  lv_tick_set_cb(HAL_GetTick);
  lv_display_t *display1 = lv_display_create(HORIZONTAL_RES, VERTICAL_RES);
  lv_display_set_buffers(display1, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
  lv_display_set_flush_cb(display1, my_flush_cb);
#if LV_USE_LOG
  lv_log_register_print_cb(lvgl_log_callback);
#endif /*LV_USE_LOG*/

  // ui_init();
  set_var_shared_lv_bat_voltage(14);
  custom_ui_init();

  monitor_memory();

  set_var_shared_lv_bat_voltage('a');
  int i = 0;
  GPIO_PinState last_state = GPIO_PIN_SET;
  GPIO_PinState current_state = GPIO_PIN_SET;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    current_state = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);

    if (last_state == GPIO_PIN_SET && current_state == GPIO_PIN_RESET)
    {
      lv_obj_t *scr_act = lv_scr_act();
      if (scr_act != NULL)
      {
        lv_obj_clean(lv_scr_act());
      }

      switch ((i++) % 4)
      {
      case 0:
        create_screen_main();
        lv_scr_load(objects.main);
        break;
      case 1:
        create_screen_tires();
        lv_scr_load(objects.tires);

        break;
      case 2:
        create_screen_inverters();
        lv_scr_load(objects.inverters);
        break;
      case 3:
        create_screen_extra();
        lv_scr_load(objects.extra);
        break;
      }

      monitor_memory();
    }

    // Aggiorna lo stato precedente
    last_state = current_state;

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    lv_timer_periodic_handler();
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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

#ifdef USE_FULL_ASSERT
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
