/*
 * ADC.h
 *
 *  Created on: Oct 8, 2018
 *      Author: skylo
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stdbool.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include "msp.h"

/******************************************************************************
 *                               Configuration                                *
 ******************************************************************************/

/**
 * Set up the ports and pins required to use the ADC channels
 */
extern void configure_ADCs(uint32_t sys_clock);
extern void configure_ADC1(uint32_t sys_clock);
extern void configure_ADC2(uint32_t sys_clock);
extern void configure_ADC3(uint32_t sys_clock);
extern void configure_ADC4(uint32_t sys_clock);


/******************************************************************************
 *                   Measurement Collection                                   *
 ******************************************************************************/
extern uint16_t measure_ADC1();
extern uint16_t measure_ADC2();
extern uint16_t measure_ADC3();
extern uint16_t measure_ADC4();


/******************************************************************************
 *                             Node Control                                   *
 ******************************************************************************/
extern void reset_ADCs();
extern void reset_ADC_1_2();
extern void reset_ADC_3_4();

extern void ADC_node_init();
extern void ADC_1_2_node_init();
extern void ADC_3_4_node_init();

extern void set_ADC_1_2_node(uint32_t node);
extern void set_ADC_3_4_node(uint32_t node);
#endif /* ADC_H_ */
