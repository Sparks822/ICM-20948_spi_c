/*
 * icm206928_spi.c
 *
 *  Created on: Feb 28, 2025
 *      Author: agana
 */

#include "icm206928_spi.h"
#include "stm32h7xx_hal.h"
#include <stdio.h>

extern SPI_HandleTypeDef hspi1;  // Use the global SPI handle

uint8_t reg;
uint8_t bank0;
uint8_t bank1;
uint8_t bank2;
uint8_t bank3;


void icm206948_init(){  
  
  HAL_Delay(100);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
  
  reg = SEL_BANK_REG; //0x7f = 0111 1111 
  bank0 = 0;

  HAL_SPI_Transmit(&hspi1, &reg1, 1, 100);
  HAL_SPI_Transmit(&hspi1, &bank0, 1, 100);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
  

}

