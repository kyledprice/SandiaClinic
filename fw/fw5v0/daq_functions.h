/*
 * daq_functions.h
 *
 *  Created on: Jan 30, 2019
 *      Author: kyleprice
 */

#ifndef DAQ_FUNCTIONS_H_
#define DAQ_FUNCTIONS_H_

#include "ti/devices/msp432e4/driverlib/driverlib.h"



/************************************************************
* DAQ status codes                                          *
************************************************************/
#define NOT_SET                 0x00
#define ID_SET                  0x01
#define VERSION_RETRIEVED       0x02
#define RES_RETRIEVED           0x04
#define SAF_SET                 0x08
#define CRNTV_SET               0x10
#define CRNT_PTRN_SET           0x20
#define GND_PTRN_SET            0x40

/************************************************************
* DAQ constants                                             *
************************************************************/
#define NUM_NODES               32
#define NUM_MEASUREMENTS        1024
#define NUM_MEAS_NODES          8

#define ADC1_OFFSET             8
#define ADC4_OFFSET             16
#define ADC3_OFFSET             32

#define DATA_RESPONCE_SIZE      (NUM_MEASUREMENTS * 2) + 3


struct inj_pair {
    uint8_t curr;
    uint8_t gnd;
};

/************************************************************
* DAQ functions                                             *
************************************************************/
extern void measure(uint8_t curr, uint8_t saf, uint16_t* data, struct inj_pair* inj_pairs, uint32_t sys_clock);
#endif /* DAQ_FUNCTIONS_H_ */
