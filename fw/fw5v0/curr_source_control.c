/*
 * curr_sourse_control.c
 *
 *  Created on: Jan 15, 2019
 *      Author: Skyler Swearngin
 */

#include <stdint.h>
#include <stdbool.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include "curr_source_control.h"

/******************************************************************************
 *                               Initialization                               *
 ******************************************************************************/

/*
 * Reset all the pins outputs to zero
 */
void curr_source_reset() {
    // Set all the ports to zero.
    GPIOA->DATA &= 0xF7;
    GPIOC->DATA &= 0x0F;
    GPIOD->DATA &= 0xFB;
    GPIOE->DATA &= 0xE0;
    GPIOG->DATA &= 0xFC;
    GPIOH->DATA &= 0xF8;
    GPIOJ->DATA &= 0xFC;
    GPIOK->DATA &= 0xF1;
    GPION->DATA &= 0xDF;
    GPIOQ->DATA &= 0xF3;
}

/*
 * Sets up all the required GPIO's as writes.
 */
void curr_source_init() {
    // Enable all the needed ports
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);

    // Set up the pins for 10-90u
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_1);

    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_2);

    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3);

    GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_1);

    GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PIN_0);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

    // Set up the pins for 100u-900u
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_0);

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);

    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_3);

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);

    // Set up the pins for 1-9m
    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_2);

    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_3);

    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);

    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_5);

    GPIOPinTypeGPIOOutput(GPIO_PORTJ_BASE, GPIO_PIN_0);

    GPIOPinTypeGPIOOutput(GPIO_PORTJ_BASE, GPIO_PIN_1);

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4);

    // Set up the pins for 10-100m
    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_2);

    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_2);

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0);

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1);

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_2);

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3);

    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_1);

    curr_source_reset();
}

/*
 * Sets up any tens values of micro amps if needed
 */
void curr_source_set_microtens(uint32_t value){
    GPIOH->DATA &= 0xF9;
    GPIOA->DATA &= 0xF7;
    switch(value) {
        case 1:
            GPIOG->DATA &= 0xFC;
            GPIOF->DATA &= 0xF9;
            break;
        case 2:
            GPIOG->DATA &= 0xFC;
            GPIOF->DATA &= 0xF9;

            GPIOF->DATA |= 0x02;
            break;
        case 3:
            GPIOG->DATA &= 0xFC;
            GPIOF->DATA &= 0xF9;

            GPIOF->DATA |= 0x04;
            break;
        case 4:
            GPIOG->DATA &= 0xFC;
            GPIOF->DATA &= 0xF9;

            GPIOF->DATA |= 0x06;
            break;
        case 5:
            GPIOG->DATA &= 0xFC;
            GPIOF->DATA &= 0xF9;

            GPIOG->DATA |= 0x01;
            break;
        case 6:
            GPIOG->DATA &= 0xFC;
            GPIOF->DATA &= 0xF9;

            GPIOG->DATA |= 0x01;
            GPIOF->DATA |= 0x02;
            break;
        case 7:
            GPIOG->DATA &= 0xFC;
            GPIOF->DATA &= 0xF9;

            GPIOG->DATA |= 0x01;
            GPIOF->DATA |= 0x04;
            break;
        case 8:
            GPIOG->DATA &= 0xFC;
            GPIOF->DATA &= 0xF9;

            GPIOG->DATA |= 0x01;
            GPIOF->DATA |= 0x06;
            break;
        case 9:
            GPIOG->DATA &= 0xFC;
            GPIOF->DATA &= 0xF9;

            GPIOG->DATA |= 0x02;
            break;
        default:
            GPIOG->DATA &= 0xFC;
            GPIOF->DATA &= 0xF9;
    }
    if(value != 0) {
        GPIOA->DATA |= 0x08;
        GPIOH->DATA |= 0x06;
    }

}

/*
 * Sets up any hundreds values of micro amps if needed
 */
void curr_source_set_microhunds(uint32_t value) {
    GPIOH->DATA &= 0xFC;
    GPIOC->DATA &= 0xEF;
    switch(value) {
        case 1:
            GPIOQ->DATA &= 0xF7;
            GPIOC->DATA &= 0x1F;
            break;
        case 2:
            GPIOQ->DATA &= 0xF7;
            GPIOC->DATA &= 0x1F;

            GPIOC->DATA |= 0x20;
            break;
        case 3:
            GPIOQ->DATA &= 0xF7;
            GPIOC->DATA &= 0x1F;

            GPIOC->DATA |= 0x40;
            break;
        case 4:
            GPIOQ->DATA &= 0xF7;
            GPIOC->DATA &= 0x1F;

            GPIOC->DATA |= 0x60;
            break;
        case 5:
            GPIOQ->DATA &= 0xF7;
            GPIOC->DATA &= 0x1F;

            GPIOC->DATA |= 0x80;
            break;
        case 6:
            GPIOQ->DATA &= 0xF7;
            GPIOC->DATA &= 0x1F;

            GPIOC->DATA |= 0xA0;
            break;
        case 7:
            GPIOQ->DATA &= 0xF7;
            GPIOC->DATA &= 0x1F;

            GPIOC->DATA |= 0xC0;
            break;
        case 8:
            GPIOQ->DATA &= 0xF7;
            GPIOC->DATA &= 0x1F;

            GPIOC->DATA |= 0xE0;
            break;
        case 9:
            GPIOQ->DATA &= 0xF7;
            GPIOC->DATA &= 0x1F;

            GPIOQ->DATA |= 0x08;
            break;
        default:
            GPIOQ->DATA &= 0xF7;
            GPIOC->DATA &= 0x1F;
    }
    if(value != 0) {
        GPIOC->DATA |= 0x10;
        GPIOH->DATA |= 0x03;
    }
}

/*
 * Sets up any valus of milli amps if needed
 */
void curr_source_set_milliones(uint32_t value) {
    GPIOD->DATA &= 0xFB;
    GPIOK->DATA &= 0xF7;
    GPIOQ->DATA &= 0xFB;
    switch(value) {
        case 1:
            GPIOE->DATA &= 0xEF;
            GPIOJ->DATA &= 0xFC;
            GPION->DATA &= 0xDF;
            break;
        case 2:
            GPIOE->DATA &= 0xEF;
            GPIOJ->DATA &= 0xFC;
            GPION->DATA &= 0xDF;

            GPIOE->DATA |= 0x10;
            break;
        case 3:
            GPIOE->DATA &= 0xEF;
            GPIOJ->DATA &= 0xFC;
            GPION->DATA &= 0xDF;

            GPIOJ->DATA |= 0x02;
            break;
        case 4:
            GPIOE->DATA &= 0xEF;
            GPIOJ->DATA &= 0xFC;
            GPION->DATA &= 0xDF;

            GPIOJ->DATA |= 0x02;
            GPIOE->DATA |= 0x10;
            break;
        case 5:
            GPIOE->DATA &= 0xEF;
            GPIOJ->DATA &= 0xFC;
            GPION->DATA &= 0xDF;

            GPIOJ->DATA |= 0x01;
            break;
        case 6:
            GPIOE->DATA &= 0xEF;
            GPIOJ->DATA &= 0xFC;
            GPION->DATA &= 0xDF;

            GPIOJ->DATA |= 0x01;
            GPIOE->DATA |= 0x10;
            break;
        case 7:
            GPIOE->DATA &= 0xEF;
            GPIOJ->DATA &= 0xFC;
            GPION->DATA &= 0xDF;

            GPIOJ->DATA |= 0x03;
            break;
        case 8:
            GPIOE->DATA &= 0xEF;
            GPIOJ->DATA &= 0xFC;
            GPION->DATA &= 0xDF;

            GPIOJ->DATA |= 0x03;
            GPIOE->DATA |= 0x10;
            break;
        case 9:
            GPIOE->DATA &= 0xEF;
            GPIOJ->DATA &= 0xFC;
            GPION->DATA &= 0xDF;

            GPION->DATA |= 0x20;
            break;
        default:
            GPIOE->DATA &= 0xEF;
            GPIOJ->DATA &= 0xFC;
            GPION->DATA &= 0xDF;
    }
    if(value != 0) {
        GPIOD->DATA |= 0x04;
        GPIOK->DATA |= 0x08;
        GPIOQ->DATA |= 0x04;
    }
}

/*
 * Sets up any tens values of milli amps if needed
 */
void curr_source_set_millitens(uint32_t value){
    GPIOQ->DATA &= 0xFB;
    GPIOK->DATA &= 0xFB;
    GPIOE->DATA &= 0xFE;
    switch(value) {
        case 1:
            GPIOE->DATA &= 0xF1;
            GPIOK->DATA &= 0xFB;
            break;
        case 2:
            GPIOE->DATA &= 0xF1;
            GPIOK->DATA &= 0xFB;

            GPIOK->DATA |= 0x02;
            break;
        case 3:
            GPIOE->DATA &= 0xF1;
            GPIOK->DATA &= 0xFD;

            GPIOE->DATA |= 0x08;
            break;
        case 4:
            GPIOE->DATA &= 0xF1;
            GPIOK->DATA &= 0xFB;

            GPIOK->DATA |= 0x02;
            GPIOE->DATA |= 0x08;
            break;
        case 5:
            GPIOE->DATA &= 0xF1;
            GPIOK->DATA &= 0xFB;

            GPIOE->DATA |= 0x04;
            break;
        case 6:
            GPIOE->DATA &= 0xF1;
            GPIOK->DATA &= 0xFB;

            GPIOK->DATA |= 0x02;
            GPIOE->DATA |= 0x04;
            break;
        case 7:
            GPIOE->DATA &= 0xF1;
            GPIOK->DATA &= 0xFB;

            GPIOE->DATA |= 0x0D;
            break;
        case 8:
            GPIOE->DATA &= 0xF1;
            GPIOK->DATA &= 0xFB;

            GPIOK->DATA |= 0x02;
            GPIOE->DATA |= 0x0D;
            break;
        case 9:
            GPIOE->DATA &= 0xF1;
            GPIOK->DATA &= 0xFB;

            GPIOE->DATA |= 0x02;
            break;
        case 10:
            GPIOE->DATA &= 0xF1;
            GPIOK->DATA &= 0xFB;

            GPIOK->DATA |= 0x02;
            GPIOE->DATA |= 0x02;
            break;
        default:
            GPIOE->DATA &= 0xF1;
            GPIOK->DATA &= 0xFD;
    }
    if(value != 0) {
        GPIOE->DATA |= 0x1;
        GPIOK->DATA |= 0x4;
        GPIOQ->DATA |= 0x4;
    }
}

/*
 * Sets up the current source such that it outputs the desired current value.
 * Breaks up the setting into the different decades to simplify the logic.
 *
 * Parameters: value - The desired current value in Microamps.
 */
void curr_source_set(uint32_t value) {
    uint32_t microtens, microhundreds, milliones, millitens;

    if(value == 0) {
        curr_source_reset();
    } else {
        millitens = value / 1000;
        milliones = (value - (millitens * 1000)) / 100;
        microhundreds = (value - (milliones * 100) - (millitens*1000)) / 10;
        microtens = (value - (milliones * 100) - (millitens*1000) - (microhundreds * 10));

        curr_source_set_microtens(microtens);
        curr_source_set_microhunds(microhundreds);
        curr_source_set_milliones(milliones);
        //curr_source_set_millitens(millitens);
    }
}
