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

#include "stm32h7xx_hal.h"

extern SPI_HandleTypeDef hspi1;  // SPI Handle

#define REG_BANK_SEL 0x7F  // Register for selecting the bank

void select_bank_0() {  
    HAL_Delay(100);
    uint8_t reg = REG_BANK_SEL;  // Register address (0x7F)
    uint8_t bank0 = 0x00;        // Bank 0 value (0000 0000)

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Chip Select LOW
    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);   // Send register address
    HAL_SPI_Transmit(&hspi1, &bank0, 1, 100); // Send value to select Bank 0
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Chip Select HIGH
}

void select_bank_1() { 
    HAL_Delay(100); 
    uint8_t reg = REG_BANK_SEL;  // Register address (0x7F)
    uint8_t bank1 = 0x10;        // Bank 1 value (0001 0000)

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Chip Select LOW
    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);   // Send register address
    HAL_SPI_Transmit(&hspi1, &bank1, 1, 100); // Send value to select Bank 1
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Chip Select HIGH
}

void select_bank_2() {  
    HAL_Delay(100);
    uint8_t reg = REG_BANK_SEL;  // Register address (0x7F)
    uint8_t bank2 = 0x20;        // Bank 2 value (0010 0000)

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Chip Select LOW
    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);   // Send register address
    HAL_SPI_Transmit(&hspi1, &bank2, 1, 100); // Send value to select Bank 2
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Chip Select HIGH
}

void select_bank_3() {  
    HAL_Delay(100);
    uint8_t reg = REG_BANK_SEL;  // Register address (0x7F)
    uint8_t bank3 = 0x30;        // Bank 3 value (0011 0000)

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Chip Select LOW
    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);   // Send register address
    HAL_SPI_Transmit(&hspi1, &bank3, 1, 100); // Send value to select Bank 3
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Chip Select HIGH
}

