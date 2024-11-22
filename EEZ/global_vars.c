/**
 * @file    global_vars.c
 * @author  Matteo Giuliani [matteo.giuliani.sc@gmail.com]
 * @date    2024-11-22 (date of creation)
 * @updated 202x-xx-xx (date of last update)
 * @version v0.0.1
 * @prefix  TMP
 *
 * @brief   Implementation of the global vars
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 
 *          see LICENSE file in the root directory of this software component
 */

/*---------- Includes --------------------------------------------------------*/

#include "global_vars.h"


/*---------- Private define --------------------------------------------------*/


/*---------- Private macro ---------------------------------------------------*/


/*---------- Private variables -----------------------------------------------*/
float shared_lv_bat_voltage;



/*---------- Private function prototypes -------------------------------------*/


/*---------- Exported Variables ----------------------------------------------*/


/*---------- Exported Functions ----------------------------------------------*/


/*---------- Private Functions -----------------------------------------------*/

float get_var_shared_lv_bat_voltage() {
    return shared_lv_bat_voltage;
}

void set_var_shared_lv_bat_voltage(float value) {
    shared_lv_bat_voltage = value;
}

