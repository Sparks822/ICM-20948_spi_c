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
#define WHO_AM_I_REG 0x00 // 

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

uint8_t read_who_am_i() {
    select_bank_0();  // Ensure we are in Bank 0 before reading WHO_AM_I
    wake_sensor();    // Wake up the sensor before reading WHO_AM_I

    uint8_t reg = WHO_AM_I_REG | 0x80; // Set MSB to 1 for read operation
    uint8_t received_data = 0;

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Chip Select LOW
    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);   // Send register address with read bit
    HAL_SPI_Receive(&hspi1, &received_data, 1, 100); // Read data from WHO_AM_I register
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Chip Select HIGH

    printf("WHO_AM_I Register: 0x%X\n", received_data); // Print the received data

    return received_data;
}

