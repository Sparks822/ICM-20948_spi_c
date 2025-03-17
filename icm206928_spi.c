#include "icm206928_spi.h"
#include "stm32h7xx_hal.h"
#include <stdio.h>
#include "stm32h7xx_hal.h"

extern SPI_HandleTypeDef hspi1;  // Use the global SPI handle



#define REG_BANK_SEL 0x7F  // Register for selecting the bank
#define WHO_AM_I_REG 0x00 //

void select_bank_0() {

    HAL_Delay(100);
    uint8_t reg = REG_BANK_SEL;  // Register address (0x7F)
    uint8_t bank0 = bank_0;        //0x00 = Bank 0 value (0000 0000)

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Chip Select LOW
    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);   // Send register address
    HAL_SPI_Transmit(&hspi1, &bank0, 1, 100); // Send value to select Bank 0
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Chip Select HIGH
}

void select_bank_1() {
    HAL_Delay(100);
    uint8_t reg = REG_BANK_SEL;  // Register address (0x7F)
    uint8_t bank1 = bank_1;        // 0x10 = Bank 1 value (0001 0000)

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Chip Select LOW
    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);   // Send register address
    HAL_SPI_Transmit(&hspi1, &bank1, 1, 100); // Send value to select Bank 1
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Chip Select HIGH
}

void select_bank_2() {
    HAL_Delay(100);
    uint8_t reg = REG_BANK_SEL;  // Register address (0x7F)
    uint8_t bank2 = bank_2;        // 0x20 = Bank 2 value (0010 0000)

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Chip Select LOW
    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);   // Send register address
    HAL_SPI_Transmit(&hspi1, &bank2, 1, 100); // Send value to select Bank 2
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Chip Select HIGH
}

void select_bank_3() {
    HAL_Delay(100);
    uint8_t reg = REG_BANK_SEL;  // Register address (0x7F)
    uint8_t bank3 = bank_3;        // 0x30 = Bank 3 value (0011 0000)

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Chip Select LOW
    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);   // Send register address
    HAL_SPI_Transmit(&hspi1, &bank3, 1, 100); // Send value to select Bank 3
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Chip Select HIGH
}

void who_am_i() {
    select_bank_0();  // Ensure we are in Bank 0 before reading WHO_AM_I

    uint8_t reg = WHO_AM_I_REG | 0x80; // 0b0000 0000 = 0b1000 0000 Set MSB to 1 for read operation
    uint8_t received_data = 0;

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);  // Chip Select LOW
    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);   // Send register address with read bit
    HAL_SPI_Receive(&hspi1, &received_data, 1, 100); // Read data from WHO_AM_I register
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);  // Chip Select HIGH

    printf("WHO_AM_I Register: 0x%X\n", received_data); // Print the received data

    return received_data;
}

void wake_sensor() {
    select_bank_0();  // Ensure we are in Bank 0

    HAL_Delay(100);
    uint8_t reg_read = PWR_MGMT_1 | 0x80;  // Read PWR_MGMT_1
    uint8_t power_mgmt = 0;

    // **Read the current value of PWR_MGMT_1**
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &reg_read, 1, 100);
    HAL_SPI_Receive(&hspi1, &power_mgmt, 1, 100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

    printf("Before Wake-Up, PWR_MGMT_1: 0x%X\n", power_mgmt);

    // **Clear the SLEEP bit (bit 6) to wake the sensor**
    // Register power_mgmt is 0x6 = 0000 0110 
    // Reset value is 0x41 = 01000001
    // (1 << 6) Shift bits 0100 0000 
    // ~(1 << 6) - invert all bits 0100 0000 = 1011 1111 
    //power_mgmt = 00000110  (binary)  = 0x06
    //mask        = 10111111  (binary)  = 0xBF
    ----------------------------------------
    // Result      = 00000110  (binary)  = 0x06 
    power_mgmt &= ~(1 << 6); // Wake up the sensor

    uint8_t reg_write = PWR_MGMT_1;  // DO NOT set MSB for write

    // **Write back the modified PWR_MGMT_1 value**
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &reg_write, 1, 100);
    HAL_SPI_Transmit(&hspi1, &power_mgmt, 1, 100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

    HAL_Delay(10); // Give the sensor time to process the wake-up

    // **Verify wake-up by reading PWR_MGMT_1 again**
    uint8_t verify = 0;
    reg_read = PWR_MGMT_1 | 0x80;  // Read PWR_MGMT_1 again

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &reg_read, 1, 100);
    HAL_SPI_Receive(&hspi1, &verify, 1, 100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

    printf("After Wake-Up, PWR_MGMT_1: 0x%X\n", verify);

    // **Check if the sensor is awake**
    if ((verify & (1 << 6)) == 0) {
        printf("Sensor is WAKE (SLEEP bit is cleared)\n");
    } else {
        printf("Sensor is still in SLEEP mode! Check SPI communication.\n");
    }
}
