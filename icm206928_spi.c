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



#define  SELECT_BANK_REG  0x7F //0X7f Base Register SELECT_BANK_REGISTER
#define  BANK0            0x00 //BIT[5:4] = 0:0 or 0FF
#define  BANK1			  0x01 //BIT[5:4] = 0:1
#define  BANK2			  0x10 //BIT[5:4] = 1:0
#define  BANK3			  0x11 //BIT[5:4] = 1:1

//Register: PWR_MGMT_1 , page 37 , Located in bank 0

#define PWR_MGMT_1   0x06  //Register Address
#define DEVICE_RESET 0x80  //Bit 7 , if set to 1 device will reset = 1000 0000 user OR operator
#define SLEEP        0X00  //Bit 6 , if set to 0 device will reset = 0000 0000 user & operator




void icm206948_SEL_BANK_REG_0() {
    HAL_Delay(100);  // Ensure sensor is stable before configuration
    printf("Initializing ICM-206948...\n");

    // Set CS to LOW (Start SPI Transaction)
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

    // Select Bank 0 - Manually transmit register and value
    uint8_t sel_reg = SELECT_BANK_REG;
    uint8_t reg_write = BANK0;

    HAL_SPI_Transmit(&hspi1, &sel_reg, 1, 100);  // Send register address
    HAL_SPI_Transmit(&hspi1, &reg_write, 1, 100);  // Send bank selection value

    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // CS HIGH

    // Read Back the Register to Verify Bank Selection
    uint8_t reg_addr = SELECT_BANK_REG | 0x80;  // Read command (MSB=1)
    uint8_t bank_value = 0xFF;  // Default invalid value

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // CS LOW

    HAL_SPI_Transmit(&hspi1, &reg_addr, 1, 100);  // Send read request
    HAL_SPI_Receive(&hspi1, &bank_value, 1, 100); // Read response

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // CS HIGH

    // ✅ Check if received data is `0x00` (Successful Bank 0 selection)
    if (bank_value == 0x00) {
        printf("[SUCCESS] Bank 0 Successfully Selected!\n");
        return 1;  // Success
    } else {
        printf("[WARNING] Bank 0 Selection Failed! Read Value: 0x%02X\n", bank_value);
        return 0;  // ❌ Failure
    }

    //Remove Sleep Wake Sensor
    HAL_Delay(100);


}
