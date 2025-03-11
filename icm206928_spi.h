/*
 * icm206928_spi.h
 *
 *  Created on: Feb 28, 2025
 *      Author: agana
 */

#ifndef INC_ICM206928_SPI_H_
#define INC_ICM206928_SPI_H_

//REG_BANK_SEL, SELECT BANK BEFORE READING/WRITING TO REGISTERS
#define  SELECT_BANK_REG  0x7F

//Read WHO_AMI_REGISTER 
#define WHO_AM_I 0X00

//Initialize the IMU Sensor

void icm206948_init();


#endif /* INC_ICM206928_SPI_H_ */
