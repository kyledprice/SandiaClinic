/*
 * ADC.c
 *
 *  Created on: Mar 12, 2019
 *      Author: Skyler Swearngin
 *      Last Edited: 4/5/19
 */

#include <stdint.h>
#include <stdbool.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include "adc.h"

/******************************************************************************
 *                               Configuration                                *
 ******************************************************************************/

/*
 * Configures all the MCU's Spi channesl for communication with the ADC's
 * Parameters: sys_clock - the clock speed the system is running at.
 */
void configure_ADCs(uint32_t sys_clock) {
    configure_ADC1(sys_clock);
    configure_ADC2(sys_clock);
    configure_ADC3(sys_clock);
    configure_ADC4(sys_clock);
}

/*
 * Configure the MCU's SPI channel for communication with the ADC's.
 * Parameters: sys_clock - the clock speed the system is running at.
 */
void configure_ADC1(uint32_t sys_clock) {
    // Enable the SSI Port and the needed GPIO ports
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {

    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {

    }

    // Configure the first pin as RX Port
    GPIOPinConfigure(GPIO_PF0_SSI3XDAT1);

    // Possibly configure the TX Port
    //GPIOPinConfigure(GPIO_PF1_SSI3XDAT0);

    //Configure the busy read line.
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_6);

    //R/C control pin and write it high
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);
    GPIOA->DATA |= 0x80;

    //Configures the fourth pin as the clk.
    GPIOPinConfigure(GPIO_PF3_SSI3CLK);

    // Set all needed GPIO pins to spi
    GPIOPinTypeSSI(GPIO_PORTF_BASE, (GPIO_PIN_0 | GPIO_PIN_3));


    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI3))
    {
    }

    // Set the SSI protocol mode, and configure the SSI clock
    SSIAdvModeSet(SSI3_BASE, SSI_ADV_MODE_LEGACY);
    SSIConfigSetExpClk(SSI3_BASE, sys_clock,
                       /*ADC protocol mode*/SSI_FRF_MOTO_MODE_0,
                       /*SSI operation mode*/SSI_MODE_MASTER,
                       /*Data transfer rate*/sys_clock/24,
                       /*Data width max 16*/ 16);

    // Enable the SSI Port
    SSIEnable(SSI3_BASE);
}

/*
 * Configure the MCU's SPI channel for communication with the ADC's.
 * Parameters: sys_clock - the clock speed the system is running at.
 */
void configure_ADC2(uint32_t sys_clock) {
    // Enable the SSI Port and the needed GPIO ports
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {

    }

    // Configure the first pin as RX Port
    GPIOPinConfigure(GPIO_PA5_SSI0XDAT1);

    // Possibly configure the TX Port
    //GPIOPinConfigure(GPIO_A4_SSI0XDAT0);

    //Configure the busy read line.
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_0);

    //R/C control pin and write it high
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_1);
    GPIOA->DATA |= 0x02;

    //Configures the fourth pin as the clk.
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);

    // Set all needed GPIO pins to spi
    GPIOPinTypeSSI(GPIO_PORTA_BASE, (GPIO_PIN_2 | GPIO_PIN_5));


    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0))
    {
    }

    // Set the SSI protocol mode, and configure the SSI clock
    SSIAdvModeSet(SSI0_BASE, SSI_ADV_MODE_LEGACY);
    SSIConfigSetExpClk(SSI0_BASE, sys_clock,
                       /*ADC protocol mode*/SSI_FRF_MOTO_MODE_0,
                       /*SSI operation mode*/SSI_MODE_MASTER,
                       /*Data transfer rate*/sys_clock/24,
                       /*Data width max 16*/ 16);

    // Enable the SSI Port
    SSIEnable(SSI0_BASE);
}

/*
 * Configure the MCU's SPI channel for communication with the ADC's.
 * Parameters: sys_clock - the clock speed the system is running at.
 */
void configure_ADC3(uint32_t sys_clock) {
    // Enable the SSI Port and the needed GPIO ports
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)) {

    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)) {

    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOP)) {

    }

    // Configure the first pin as RX Port
    GPIOPinConfigure(GPIO_PE5_SSI1XDAT1);

    // Possibly configure the TX Port
    //GPIOPinConfigure(GPIO_E4_SSI1XDAT0);

    //Configure the busy read line.
    GPIOPinTypeGPIOInput(GPIO_PORTP_BASE, GPIO_PIN_0);

    //R/C control pin and write it high
    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_1);
    GPIOP->DATA |= 0x02;

    //Configures the fourth pin as the clk.
    GPIOPinConfigure(GPIO_PB5_SSI1CLK);

    // Set all needed GPIO pins to spi
    GPIOPinTypeSSI(GPIO_PORTB_BASE, GPIO_PIN_5);
    GPIOPinTypeSSI(GPIO_PORTE_BASE, GPIO_PIN_5);


    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI1))
    {
    }

    // Set the SSI protocol mode, and configure the SSI clock
    SSIAdvModeSet(SSI1_BASE, SSI_ADV_MODE_LEGACY);
    SSIConfigSetExpClk(SSI1_BASE, sys_clock,
                       /*ADC protocol mode*/SSI_FRF_MOTO_MODE_0,
                       /*SSI operation mode*/SSI_MODE_MASTER,
                       /*Data transfer rate*/sys_clock/24,
                       /*Data width max 16*/ 16);

    // Enable the SSI Port
    SSIEnable(SSI1_BASE);
}

/*
 * Configure the MCU's SPI channel for communication with the ADC's.
 * Parameters: sys_clock - the clock speed the system is running at.
 */
void configure_ADC4(uint32_t sys_clock) {
    // Enable the SSI Port and the needed GPIO ports
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){

    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOQ)){

    }

    // Configure the first pin as RX Port
    // Test and see if things measure without the transmit port being enabled first
    GPIOPinConfigure(GPIO_PD0_SSI2XDAT1);
    //GPIOPinConfigure(GPIO_PD1_SSI2XDAT0);

    // Configure pin to read the ADC's busy line.
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_1);


    // Configure R/C control pin and write it high
    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_1);
    GPIOQ->DATA |= 0x02;

    // Configures the fourth pin as the clk.
    GPIOPinConfigure(GPIO_PD3_SSI2CLK);

    // Configure all the needed GPIO pins as SSI
    GPIOPinTypeSSI(GPIO_PORTD_BASE, (GPIO_PIN_0 | GPIO_PIN_3));


    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI2))
    {
    }
    // Set the SSI protocol mode, and configure the SSI clock
    SSIAdvModeSet(SSI2_BASE, SSI_ADV_MODE_LEGACY);
    SSIConfigSetExpClk(SSI2_BASE, sys_clock,
                       /*ADC protocol mode*/SSI_FRF_MOTO_MODE_0,
                       /*SSI operation mode*/SSI_MODE_MASTER,
                       /*Data transfer rate*/sys_clock/24,
                       /*Data width max 16*/ 16);

    // Enable the SSI Port
    SSIEnable(SSI2_BASE);
}


/******************************************************************************
 *                   Measurement Collection                                   *
 ******************************************************************************/

/*
 * Measure the data from the ADC's and stores it in a local variable
 */
uint16_t measure_ADC1() {
    // Replace with a parameter passed into the function.
    uint16_t data = 100;

    // Perform a non-blocking read to clear out the ssi regester
    while(SSIDataGetNonBlocking(SSI3_BASE, &data)) {

    }

    // Write the pin R/C pin low
    GPIOA->DATA &= 0x7F;

    // Hold it low for the time required by ADC. Find a better way to do this
    SysCtlDelay(1);

    // Set the pin back to high.
    GPIOA->DATA |= 0x80;

    // Delay while the busy pin is high, for no just add sys delay.
    //SysCtlDelay(100);
    // Read data from ADC rx bus and save to an array.
    SSIDataPut(SSI3_BASE, 0xFFFF);
    // Have to write to send out clock, wait while write is happening
    while(SSIBusy(SSI3_BASE));
    SSIDataGet(SSI3_BASE, &data);

    // Data was comming back as 2's complement this method zeros out the sign bit
    // which is unimportant for your calculations.
    data &= 0x7FFF;
    return data;
}

/*
 * Measure the data from the ADC's and stores it in a local variable
 */
uint16_t measure_ADC2() {
    // Eventually replace this with a parameter passed into the function.
    uint16_t data = 10;

    // Perform a non-blocking read to clear out the ssi regester
    while(SSIDataGetNonBlocking(SSI0_BASE, &data)) {

    }

    // Write the pin R/C pin low
    GPIOA->DATA &= 0xFD;

    // Hold it low for the time required by ADC. Find a better way to do this
    SysCtlDelay(1);

    // Set the pin back to high.
    GPIOA->DATA |= 0x02;

    // Delay while the busy pin is high, for no just add sys delay.
    //SysCtlDelay(10);
    // Read data from ADC rx bus and save to an array.
    SSIDataPut(SSI0_BASE, 0xFFFF);
    // Have to write to send out clock, wait while write is happening
    while(SSIBusy(SSI0_BASE));
    SSIDataGet(SSI0_BASE, &data);
    data &= 0x7FFF;
    return data;
}

/*
 * Measure the data from the ADC's and stores it in a local variable
 */
uint16_t measure_ADC3() {
    // Eventually replace this with a parameter passed into the function.
    uint16_t data = 10;

    // Perform a non-blocking read to clear out the ssi regester
    while(SSIDataGetNonBlocking(SSI1_BASE, &data)) {

    }

    // Write the pin R/C pin low
    GPIOP->DATA &= 0xFD;

    // Hold it low for the time required by ADC. Find a better way to do this
    SysCtlDelay(1);

    // Set the pin back to high.
    GPIOP->DATA |= 0x02;

    // Delay while the busy pin is high, for no just add sys delay.
    //SysCtlDelay(100);
    // Read data from ADC rx bus and save to an array.
    SSIDataPut(SSI1_BASE, 0xFFFF);
    // Have to write to send out clock, wait while write is happening
    while(SSIBusy(SSI1_BASE));
    SSIDataGet(SSI1_BASE, &data);

    // Data from adc comes back as 2's complement this operation zeros out the sign
    // bit which is unimportant for your calculations.
    data &= 0x7FFF;
    return data;
}

/*
 * Measure the data from the ADC's and stores it in a local variable
 */
uint16_t measure_ADC4() {
    // Set R/C pin low and wait for 50ns then go high again.
    uint16_t data = 0;

    while(SSIDataGetNonBlocking(SSI2_BASE, &data)) {

    }

    // Write the pin low.
    GPIOQ->DATA &= 0xFD;
    //GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_2, 0x0);
    SysCtlDelay(1);
    // Set the pin back to high.
    //GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_2, 0x1);
    GPIOQ->DATA |= 0x02;

    // Wait while the busy pin is high.
    //SysCtlDelay(100);
    //while(!GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1));
    // Read data from ADC rx bus and save to an array.
    SSIDataPut(SSI2_BASE, 0xFFFF);
    while(SSIBusy(SSI2_BASE));
    SSIDataGet(SSI2_BASE, &data);
    data &= 0x7FFF;
    return data;
}


/******************************************************************************
 *                             Node Control                                   *
 ******************************************************************************/

/*
 * Resets all the ADC's node control to an off state
 */
void reset_ADCs() {
    reset_ADC_1_2();
    reset_ADC_3_4();
}
/*
 * Set the ADC to not be looking at any measurement node.
 */ 
void reset_ADC_1_2() {
    GPIOL->DATA &= 0xFD;
    GPIOM->DATA &= 0xFD;
}

/*
 * Set the ADC to not be looking at any measurement node.
 */ 
void reset_ADC_3_4(){
    GPIOP->DATA &= 0xBF;
    GPION->DATA &= 0xEC;
}

/*
 * Initialized all pins needed for ADC measurment node control.
 */
void ADC_node_init() {
    ADC_1_2_node_init();
    ADC_3_4_node_init();
}

/*
 * Enable and initialize all the pins used to control the measurement node.
 */
void ADC_1_2_node_init() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);

    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_0);

    reset_ADC_1_2();
}

/*
 * Enable and initialize all the pins used to control the measurement node.
 */
void ADC_3_4_node_init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);

    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_4);

    reset_ADC_3_4();
}

/*
 * Selects which node the ADC's will measure from.
 * Parameters: node - The desired measurement node, 
 * to get the second adc's measurement node add 8 to this number.
 */
void set_ADC_1_2_node(uint32_t node) {
    GPIOL->DATA &= 0xFD;
    switch(node) {
    case 1:
    case 9:
        GPIOL->DATA &= 0xFC;
        GPIOM->DATA &= 0xFC;
        break;
    case 2:
    case 10:
        GPIOL->DATA &= 0xFC;
        GPIOM->DATA &= 0xFC;

        GPIOL->DATA |= 0x01;
        break;
    case 3:
    case 11:
        GPIOL->DATA &= 0xFC;
        GPIOM->DATA &= 0xFC;

        GPIOM->DATA |= 0x01;
        break;
    case 4:
    case 12:
        GPIOL->DATA &= 0xFC;
        GPIOM->DATA &= 0xFC;

        GPIOL->DATA |= 0x01;
        GPIOM->DATA |= 0x01;
        break;
    case 5:
    case 13:
        GPIOL->DATA &= 0xFC;
        GPIOM->DATA &= 0xFC;

        GPIOM->DATA |= 0x02;
        break;
    case 6:
    case 14:
        GPIOL->DATA &= 0xFC;
        GPIOM->DATA &= 0xFC;

        GPIOM->DATA |= 0x02;
        GPIOL->DATA |= 0x01;
        break;
    case 7:
    case 15:
        GPIOL->DATA &= 0xFC;
        GPIOM->DATA &= 0xFC;

        GPIOM->DATA |= 0x03;
        break;
    case 8:
    case 16:
        GPIOL->DATA &= 0xFC;
        GPIOM->DATA &= 0xFC;

        GPIOM->DATA |= 0x03;
        GPIOL->DATA |= 0x01;
        break;
    default:
        reset_ADC_1_2();
    }
    GPIOL->DATA |= 0x02;
}

/*
 * Selects which node the ADC's will measure from.
 * Parameters: node - The desired measurement node, 
 * to get the second adc's measurement node add 8 to this number.
 */
void set_ADC_3_4_node(uint32_t node) {
    GPION->DATA &= 0xEF;
    switch(node) {
    case 1:
    case 9:
        GPION->DATA &= 0xFC;
        GPIOP->DATA &= 0xDF;
        break;
    case 2:
    case 10:
        GPION->DATA &= 0xFC;
        GPIOP->DATA &= 0xDF;

        GPION->DATA |= 0x02;
        break;
    case 3:
    case 11:
        GPION->DATA &= 0xFC;
        GPIOP->DATA &= 0xDF;

        GPION->DATA |= 0x01;
        break;
    case 4:
    case 12:
        GPION->DATA &= 0xFC;
        GPIOP->DATA &= 0xDF;

        GPION->DATA |= 0x03;
        break;
    case 5:
    case 13:
        GPION->DATA &= 0xFC;
        GPIOP->DATA &= 0xDF;

        GPIOP->DATA |= 0x20;
        break;
    case 6:
    case 14:
        GPION->DATA &= 0xFC;
        GPIOP->DATA &= 0xDF;

        GPIOP->DATA |= 0x20;
        GPION->DATA |= 0x02;
        break;
    case 7:
    case 15:
        GPION->DATA &= 0xFC;
        GPIOP->DATA &= 0xDF;

        GPIOP->DATA |= 0x20;
        GPION->DATA |= 0x01;
        break;
    case 8:
    case 16:
        GPION->DATA &= 0xFC;
        GPIOP->DATA &= 0xDF;

        GPIOP->DATA |= 0x20;
        GPION->DATA |= 0x03;
        break;
    default:
        reset_ADC_3_4();
    }
    GPION->DATA |= 0x10;
}
