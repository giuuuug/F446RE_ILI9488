/**
 * @file    log.c
 * @author  Matteo Giuliani [matteo.giuliani.sc@gmail.com]
 * @date    2024-11-20 (date of creation)
 * @updated 202x-xx-xx (date of last update)
 * @version v0.0.1
 * @prefix  TMP
 *
 * @brief   Source code for the LVGL log 
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 
 *          see LICENSE file in the root directory of this software component
 */

/*---------- Includes --------------------------------------------------------*/
#include "log.h"


/*---------- Private define --------------------------------------------------*/


/*---------- Private macro ---------------------------------------------------*/


/*---------- Private variables -----------------------------------------------*/


/*---------- Private function prototypes -------------------------------------*/


/*---------- Exported Variables ----------------------------------------------*/


/*---------- Exported Functions ----------------------------------------------*/


/*---------- Private Functions -----------------------------------------------*/
#if LV_USE_LOG

void lvgl_log_callback(lv_log_level_t level, const char * buf)
{
   char log_msg[256]; // Adatta la dimensione alle tue esigenze

    // Identifica il tipo di log in base al livello
    const char *level_str;
    switch (level) {
        case LV_LOG_LEVEL_TRACE:
            level_str = "TRACE: ";
            break;
        case LV_LOG_LEVEL_INFO:
            level_str = "INFO: ";
            break;
        case LV_LOG_LEVEL_WARN:
            level_str = "WARN: ";
            break;
        case LV_LOG_LEVEL_ERROR:
            level_str = "ERROR: ";
            break;
        default:
            level_str = "LOG: "; // Caso generico
            break;
    }


    snprintf(log_msg, sizeof(log_msg), "%s%s\r\n", level_str, buf);

    HAL_UART_Transmit(&huart2, (uint8_t*)log_msg, strlen(log_msg), HAL_MAX_DELAY);
}

#endif  /*LV_USE_LOG*/