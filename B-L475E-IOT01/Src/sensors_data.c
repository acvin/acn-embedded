/**
  ******************************************************************************
  * @file    sensors_data.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    28-March-2017
  * @brief   Manage sensors of STM32L475 IoT board.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "sensors_data.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include "stm32l4xx_hal.h"
#include "stm32l475e_iot01.h"
#include "stm32l475e_iot01_tsensor.h"
#include "stm32l475e_iot01_hsensor.h"
#include "stm32l475e_iot01_psensor.h"
#include "stm32l475e_iot01_magneto.h"
#include "stm32l475e_iot01_gyro.h"
#include "stm32l475e_iot01_accelero.h"
#include "vl53l0x_proximity.h"

#include <debug.h>

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

/**
  * @brief  init_sensors
  * @param  none
  * @retval 0 in case of success
  *         -1 in case of failure
  */
int init_sensors(void)
{
  int ret = 0;
  
  if (HSENSOR_OK != BSP_HSENSOR_Init()) {
    DBG("BSP_HSENSOR_Init() returns %d\n", ret);
    ret = -1;
  }
  
  if (TSENSOR_OK != BSP_TSENSOR_Init()) {
    DBG("BSP_TSENSOR_Init() returns %d\n", ret);
    ret = -1;
  }
  
  if (PSENSOR_OK != BSP_PSENSOR_Init()) {
    DBG("BSP_PSENSOR_Init() returns %d\n", ret);
    ret = -1;
  }
  
  if (MAGNETO_OK != BSP_MAGNETO_Init()) {
    DBG("BSP_MAGNETO_Init() returns %d\n", ret);
    ret = -1;
  }

  if (GYRO_OK != BSP_GYRO_Init()) {
    DBG("BSP_GYRO_Init() returns %d\n", ret);
    ret = -1;
  }
  
  if (ACCELERO_OK != BSP_ACCELERO_Init()) {
    DBG("BSP_ACCELERO_Init() returns %d\n", ret);
    ret = -1;
  }
    
  VL53L0X_PROXIMITY_Init();
    
  return ret;
}

/**
  * @brief  fill the payload with the sensor values
  * @param  none
  * @param sensor_data_t is the char pointer for the data to be filled
  * @retval 0 in case of success
  *         -1 in case of failure
  */
int PrepareMqttPayload(void *v) {
  sensors_data_t *sd = (sensors_data_t*)v;
  sd->temperature = BSP_TSENSOR_ReadTemp();
  sd->humidity = BSP_HSENSOR_ReadHumidity();
  sd->pressure = BSP_PSENSOR_ReadPressure();
  sd->proximity = VL53L0X_PROXIMITY_GetDistance();
  BSP_ACCELERO_AccGetXYZ(sd->acc);
  BSP_GYRO_GetXYZ(sd->gyr);     
  BSP_MAGNETO_GetXYZ(sd->mag);
  DBG("data: temp(%.2f) acc{%.2f, %.2f, %.2f}",
      sd->temperature,
      (float)sd->acc[0],
      (float)sd->acc[1],
      (float)sd->acc[2]);
  BSP_LED_Toggle(LED_GREEN);
  return 0;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
