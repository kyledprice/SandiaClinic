/*
 * projection_cont.c
 *
 *  Created on: Feb 19, 2019
 *      Author: Skyler Swearngin
 */
#include <stdint.h>
#include <stdbool.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include "projection_cont.h"


/******************************************************************************
 *                               Initiation                                   *
 ******************************************************************************/


void proj_init() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);

    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_4);

    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_3);

    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_4);

    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_2);

    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_2);

    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_2);

    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_4);

    proj_reset();
}


/******************************************************************************
 *                                 Reset                                      *
 ******************************************************************************/

void proj_reset() {
    current_proj_reset();
    gnd_proj_reset();
}

/*
 * Reset the output of all the GPIO pins connected to the switches to zero.
 */
void current_proj_reset() {
    GPIOH->DATA &= 0xF7;
    GPIOK->DATA &= 0x8F;
    GPIOM->DATA &= 0x03;
}

/*
 * Reset the output of all the GPIO pins connected to the switches to zero.
 */
void gnd_proj_reset() {
    GPIOK->DATA &= 0x7F;
    GPIOD->DATA &= 0x7F;
    GPIOP->DATA &= 0xF1;
    GPIOQ->DATA &= 0xEF;
    GPIOL->DATA &= 0xD3;
}

/******************************************************************************
 *                                 Control                                    *
 ******************************************************************************/

/*
 * Set the switches to output the desired node.
 */
void current_proj_set(uint32_t node) {
    // TODO Also backwards as all fuck. Try to figure it out.
    int set_node = node;

    GPIOM->DATA &= 0x03;
    GPIOD->DATA &= 0xEF;
    GPIOH->DATA &= 0xF7;
    switch(set_node) {
        case 1:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;
            break;
        case 2:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOM->DATA |= 0x80;
            break;
        case 3:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOK->DATA |= 0x10;
            break;
        case 4:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOM->DATA |= 0x80;
            GPIOK->DATA |= 0x10;
            break;
        case 5:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOK->DATA |= 0x20;
            break;
        case 6:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOM->DATA |= 0x80;
            GPIOK->DATA |= 0x20;
            break;
        case 7:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOK->DATA |= 0x30;
            break;
        case 8:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOM->DATA |= 0x80;
            GPIOK->DATA |= 0x30;
            break;
        case 9:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOK->DATA |= 0x40;
            break;
        case 10:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOM->DATA |= 0x80;
            GPIOK->DATA |= 0x40;
            break;
        case 11:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOK->DATA |= 0x50;
            break;
        case 12:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOM->DATA |= 0x80;
            GPIOK->DATA |= 0x50;
            break;
        case 13:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOK->DATA |= 0x60;
            break;
        case 14:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOM->DATA |= 0x80;
            GPIOK->DATA |= 0x60;
            break;
        case 15:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOK->DATA |= 0x70;
            break;
        case 16:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOM->DATA |= 0x80;
            GPIOK->DATA |= 0x70;
            break;
        case 17:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            break;
        case 18:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x08;
            break;
        case 19:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x10;
            break;
        case 20:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x18;
            break;
        case 21:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x20;
            break;
        case 22:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x28;
            break;
        case 23:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x30;
            break;
        case 24:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x38;
            break;
        case 25:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x40;
            break;
        case 26:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x48;
            break;
        case 27:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x50;
            break;
        case 28:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x58;
            break;
        case 29:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x60;
            break;
        case 30:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x68;
            break;
        case 31:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;


            GPIOM->DATA |= 0x70;
            break;
        case 32:
            GPIOK->DATA &= 0x8F;
            GPIOM->DATA &= 0x03;

            GPIOM->DATA |= 0x78;
            break;
        default:
            current_proj_reset();
    }
    if(node != 0) {
        if(node > 16) {
            // Enable lower
            GPIOM->DATA |= 0x04;
        } else {
            // Enable upper
            GPIOH->DATA |= 0x08;
            GPIOD->DATA |= 0x10;
        }

    }
    GPIOH->DATA |= 0x07;
}

/*
 * Set the switches to output the desired node.
 */
void gnd_proj_set(uint32_t node) {
    // TODO Stuff is backwards as fuck, fix later
    GPIOD->DATA &= 0x3F;
    GPIOK->DATA &= 0x7F;
    switch(node) {
    case 1:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x00;
        GPIOP->DATA |= 0x00;
        break;
    case 2:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x10;
        GPIOP->DATA |= 0x00;
        break;
    case 3:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x00;
        GPIOP->DATA |= 0x04;
        break;
    case 4:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x10;
        GPIOP->DATA |= 0x04;
        break;
    case 5:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x00;
        GPIOP->DATA |= 0x08;
        break;
    case 6:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x10;
        GPIOP->DATA |= 0x08;
        break;
    case 7:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x00;
        GPIOP->DATA |= 0x0D;
        break;
    case 8:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x10;
        GPIOP->DATA |= 0x0D;
        break;
    case 9:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x00;
        GPIOP->DATA |= 0x10;
        break;
    case 10:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x10;
        GPIOP->DATA |= 0x10;
        break;
    case 11:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x00;
        GPIOP->DATA |= 0x14;
        break;
    case 12:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x10;
        GPIOP->DATA |= 0x14;
        break;
    case 13:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x00;
        GPIOP->DATA |= 0x18;
        break;
    case 14:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x10;
        GPIOP->DATA |= 0x18;
        break;
    case 15:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x00;
        GPIOP->DATA |= 0x1D;
        break;
    case 16:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOQ->DATA |= 0x10;
        GPIOP->DATA |= 0x1D;
        break;
    case 17:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x00;
        break;
    case 18:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x20;
        break;
    case 19:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x10;
        break;
    case 20:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x30;
        break;
    case 21:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x08;
        break;
    case 22:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x28;
        break;
    case 23:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x18;
        break;
    case 24:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x38;
        break;
    case 25:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x04;
        break;
    case 26:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x24;
        break;
    case 27:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x14;
        break;
    case 28:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x34;
        break;
    case 29:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x0D;
        break;
    case 30:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x2D;
        break;
    case 31:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x1D;
        break;
    case 32:
        GPIOP->DATA &= 0xE3;
        GPIOQ->DATA &= 0xEF;
        GPIOL->DATA &= 0xD3;

        GPIOL->DATA |= 0x3D;
        break;
    default:
        gnd_proj_reset();
    }
    if(node != 0) {
        if(node > 16) {
            // Enable upper
            GPIOD->DATA |= 0x20;
        } else {
            // Enable lower
            GPIOD->DATA |= 0x40;
            GPIOK->DATA |= 0x80;
        }
    }
}




