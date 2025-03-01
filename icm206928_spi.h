/*
 * icm206928_spi.h
 *
 *  Created on: Feb 28, 2025
 *      Author: agana
 */

#ifndef INC_ICM206928_SPI_H_
#define INC_ICM206928_SPI_H_

//Bank Select Register 0,1,2,3 on Regitser 7fH or 7F in hexadecimal

#define  SELECT_BANK_REG  0x7F //0X7f Base Register SELECT_BANK_REGISTER
#define  BANK0            0x00 //BIT[5:4] = 0:0 or 0FF , use & AND    Operator to bit 5 and 4 to 0
#define  BANK1			  0x01 //BIT[5:4] = 0:1 use
#define  BANK2			  0x10 //BIT[5:4] = 1:0 use
#define  BANK3			  0x11 //BIT[5:4] = 1:1

//PWR_MGMT_1 , page 37 , Located in bank 0

#define PWR_MGMT_1   0x06  //Register Address
#define DEVICE_RESET 0x80  //Bit 7 , if set to 1 device will reset = 1000 0000 user OR operator
#define SLEEP        0X00  //Bit 6 , if set to 0 device will reset = 0000 0000 user & operator


//Initialize the IMU Sensor

void icm206948_init();


#endif /* INC_ICM206928_SPI_H_ */
