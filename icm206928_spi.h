/*
 * icm206928_spi.h
 *
 *  Created on: Feb 28, 2025
 *      Author: agana
 */

#ifndef INC_ICM206928_SPI_H_
#define INC_ICM206928_SPI_H_

//Bank Select Register 0,1,2,3 on Regitser 7fH or 7F in hexadecimal

#define  REG_BANK_SEL 	0x7F   // Register for selecting the bank
#define  bank_0 			0x00   // Bank 0 value (0000 0000)
#define  bank_1 			0x10   // Bank 1 value (0001 0000)
#define  bank_2 			0x20   // Bank 2 value (0010 0000)
#define  bank_3 			0x30   // Bank 3 value (0011 0000)


//PWR_MGMT_1 , page 37 , Located in bank 0

#define PWR_MGMT_1    0x06   //Register Address
#define WHO_AM_I     0X00  //

//Initialize the IMU Sensor

void select_bank0();
void who_am_i();


#endif /* INC_ICM206928_SPI_H_ */
