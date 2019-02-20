/*
 * main.c
 *
 *  Created on: Jan 3, 2019
 *      Author: kyleprice
 */

#ifndef CDC_CODE

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include "ti/usblib/msp432e4/usblib.h"
#include "ti/usblib/msp432e4/usbcdc.h"
#include "ti/usblib/msp432e4/usb-ids.h"
#include "ti/usblib/msp432e4/device/usbdevice.h"
#include "ti/usblib/msp432e4/device/usbdcdc.h"
#include "ustdlib.h"
#include "pinout.h"
#include "usb_structs.h"

#include "usb_functions.h"
#include "daq_functions.h"

#endif

//****************************************************************************
//
//! \addtogroup example_list
//! <h1>USB CDC Serial Device (usb_dev_cdc_serial)</h1>
//!
//! This example application turns the evaluation kit into a CDC device
//! when connected to the USB host system.  The application
//! supports the USB Communication Device Class, Abstract Control Model to
//! by interacting with the USB host via a virtual COM port.  For this example,
//! the evaluation kit will enumerate as a CDC device with one virtual
//! serial port.
//!
//! Once the virtual COM port is opened, the user should see a continuous
//! display of "Press any key" command.  When any key is pressed, the
//! CDC device will then respond back with 'Received the key press'.
//!
//! A Windows INF driver file for the device is provided
//! in the <simplelink_install_folder>/tools/usblib/windows_drivers directory.
//!  This INF contains information required to install CDC driver on the
//! Windows OS>.
//!
//! Set baudrate = 115200, 8:1
//!
//*****************************************************************************

//****************************************************************************
//
// The system tick rate expressed both as ticks per second and a millisecond
// period.
//
//****************************************************************************
#define SYSTICKS_PER_SECOND 100
#define SYSTICK_PERIOD_MS (1000 / SYSTICKS_PER_SECOND)

//*****************************************************************************
//
// Variable to remember our clock frequency
//
//*****************************************************************************
uint32_t g_ui32SysClock = 0;

//****************************************************************************
//
// Variables tracking transmit and receive counts.
//
//****************************************************************************
volatile uint32_t g_ui32UARTTxCount = 0;
volatile uint32_t g_ui32UARTRxCount = 0;

//****************************************************************************
//
// Default line coding settings for the redirected UART.
//
//****************************************************************************
#define DEFAULT_BIT_RATE        115200
#define DEFAULT_UART_CONFIG     (UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | \
                                 UART_CONFIG_STOP_ONE)

//****************************************************************************
//
// GPIO peripherals and pins muxed with the redirected UART.  These will
// depend upon the IC in use and the UART selected in UART0_BASE.  Be careful
// that these settings all agree with the hardware you are using.
//
//****************************************************************************
#define TX_GPIO_BASE            GPIO_PORTA_BASE
#define TX_GPIO_PERIPH          SYSCTL_PERIPH_GPIOA
#define TX_GPIO_PIN             GPIO_PIN_1

#define RX_GPIO_BASE            GPIO_PORTA_BASE
#define RX_GPIO_PERIPH          SYSCTL_PERIPH_GPIOA
#define RX_GPIO_PIN             GPIO_PIN_0

//****************************************************************************
//
// The LED control macros.
//
//****************************************************************************
#define LEDOn()  ROM_GPIOPinWrite(CLP_D1_PORT, CLP_D1_PIN, CLP_D1_PIN);

#define LEDOff() ROM_GPIOPinWrite(CLP_D1_PORT, CLP_D1_PIN, 0)
#define LEDToggle()                                                         \
        ROM_GPIOPinWrite(CLP_D1_PORT, CLP_D1_PIN,                           \
                         (ROM_GPIOPinRead(CLP_D1_PORT, CLP_D1_PIN) ^        \
                          CLP_D1_PIN));


//****************************************************************************
//
// Defines the size of the buffer that holds the command line.
//
//****************************************************************************
#define CMD_BUF_SIZE            256

//****************************************************************************
//
// The buffer that holds the command line.
//
//****************************************************************************
static char g_pcCmdBuf[CMD_BUF_SIZE];
static uint32_t ui32CmdIdx;

//****************************************************************************
//
// Flag indicating whether or not we are currently sending a Break condition.
//
//****************************************************************************
//static bool g_bSendingBreak = false;

//****************************************************************************
//
// Global system tick counter
//
//****************************************************************************
volatile uint32_t g_ui32SysTickCount = 0;


//****************************************************************************
//
// Flags used to pass commands from interrupt context to the main loop.
//
//****************************************************************************
#define COMMAND_RECEIVED        0x00000001
#define COMMAND_TRANSMIT_COMPLETE  0x00000002


volatile uint32_t g_ui32Flags = 0;

//****************************************************************************
//
// Global flag indicating that a USB configuration has been set.
//
//****************************************************************************
static volatile bool g_bUSBConfigured = false;

//****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1)
    {
    }
}
#endif

extern void USB0_IRQDeviceHandler(void);
//This dummy handler created as a hack for USB interrupt in
//startup file.  When the USB interrupt has attribute of 'weak'
//and usb.lib is linked to project, the interrupt handler in
//../device/usbdhandler.c file is routed
//to default handler.  The 'weak' attribute only works for
//dynamic libraries and not static library
void USB0_IRQHandler(void)
{

    USB0_IRQDeviceHandler();
}


//****************************************************************************
//
// Interrupt handler for the system tick counter.
//
//****************************************************************************
void
SysTick_Handler(void)
{
    //
    // Update our system time.
    //
    g_ui32SysTickCount++;
}


//****************************************************************************
//
// Get the communication parameters in use on the CDC terminal.
//
//****************************************************************************
static void
GetLineCoding(tLineCoding *psLineCoding)
{
    //
    // Get the current line coding set for the CDC terminal.
    //
    psLineCoding->ui32Rate = DEFAULT_BIT_RATE;
    psLineCoding->ui8Databits = 8;
    psLineCoding->ui8Parity = USB_CDC_PARITY_NONE;
    psLineCoding->ui8Stop = USB_CDC_STOP_BITS_1;

}


//****************************************************************************
//
// Handles CDC driver notifications related to control and setup of the
// device.
//
// \param pvCBData is the client-supplied callback pointer for this channel.
// \param ui32Event identifies the event we are being notified about.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the CDC driver to perform control-related
// operations on behalf of the USB host.  These functions include setting
// and querying the serial communication parameters, setting handshake line
// states and sending break conditions.
//
// \return The return value is event-specific.
//
//****************************************************************************
uint32_t
ControlHandler(void *pvCBData, uint32_t ui32Event,
               uint32_t ui32MsgValue, void *pvMsgData)
{

    //
    // Which event are we being asked to process?
    //
    switch(ui32Event)
    {
        //
        // We are connected to a host and communication is now possible.
        //
        case USB_EVENT_CONNECTED:
        {
            g_bUSBConfigured = true;
            g_ui32Flags |= COMMAND_TRANSMIT_COMPLETE;

            //
            // Flush our buffers.
            //
            USBBufferFlush(&g_psTxBuffer);
            USBBufferFlush(&g_psRxBuffer);

            break;
        }

        //
        // The host has disconnected.
        //
        case USB_EVENT_DISCONNECTED:
        {
            g_bUSBConfigured = false;
            break;
        }

        //
        // Return the current serial communication parameters.
        //
        case USBD_CDC_EVENT_GET_LINE_CODING:
        {
            GetLineCoding(pvMsgData);
            break;
        }

        //
        // Set the current serial communication parameters.
        //
        case USBD_CDC_EVENT_SET_LINE_CODING:
        {
//            SetLineCoding(pvMsgData);
            break;
        }

        //
        // Set the current serial communication parameters.
        //
        case USBD_CDC_EVENT_SET_CONTROL_LINE_STATE:
        {
//            SetControlLineState((unsigned short)ui32MsgValue);
            break;
        }

        //
        // Send a break condition on the serial line.
        //
        case USBD_CDC_EVENT_SEND_BREAK:
        {
            break;
        }

        //
        // Clear the break condition on the serial line.
        //
        case USBD_CDC_EVENT_CLEAR_BREAK:
        {
            break;
        }

        //
        // Ignore SUSPEND and RESUME for now.
        //
        case USB_EVENT_SUSPEND:
        case USB_EVENT_RESUME:
        {
            break;
        }

        //
        // We don't expect to receive any other events.  Ignore any that show
        // up in a release build or hang in a debug build.
        //
        default:
        {
            break;
        }
    }

    return(0);
}



//****************************************************************************
//
// Handles CDC driver notifications related to the transmit channel (data to
// the USB host).
//
// \param ui32CBData is the client-supplied callback pointer for this channel.
// \param ui32Event identifies the event we are being notified about.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the CDC driver to notify us of any events
// related to operation of the transmit data channel (the IN channel carrying
// data to the USB host).
//
// \return The return value is event-specific.
//
//****************************************************************************
uint32_t
TxHandlerCmd(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue,
             void *pvMsgData)
{
    //
    // Which event have we been sent?
    //
    switch(ui32Event)
    {
        case USB_EVENT_TX_COMPLETE:
        {
            //
            // Clear the flag
            //
            g_ui32Flags |= COMMAND_TRANSMIT_COMPLETE;

            break;
        }

        //
        // We don't expect to receive any other events.  Ignore any that show
        // up in a release build or hang in a debug build.
        //
        default:
        {
            break;
        }
    }
    return(0);
}



//****************************************************************************
//
// Handles CDC driver notifications related to the receive channel (data from
// the USB host).
//
// \param ui32CBData is the client-supplied callback data value for this
// channel.
// \param ui32Event identifies the event we are being notified about.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the CDC driver to notify us of any events
// related to operation of the receive data channel (the OUT channel carrying
// data from the USB host).
//
// \return The return value is event-specific.
//
//****************************************************************************

uint32_t
RxHandlerCmd(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue,
             void *pvMsgData)
{
    const tUSBDCDCDevice *psCDCDevice;
    const tUSBBuffer *pBufferRx;

    switch(ui32Event)
    {
        //
        // A new packet has been received.
        //
        case USB_EVENT_RX_AVAILABLE:
        {
            //
            // Create a device pointer.
            //
            psCDCDevice = (const tUSBDCDCDevice *)pvCBData;
            pBufferRx = (const tUSBBuffer *)psCDCDevice->pvRxCBData;

            g_pcCmdBuf[ui32CmdIdx] = 0;
            ui32CmdIdx = 0;

            //
            // Keep reading characters as long as there are more to receive.
            //
            if(USBBufferRead(pBufferRx,
                            (uint8_t *)&g_pcCmdBuf[ui32CmdIdx], 256))
            {


                //
                // Indicate that a command has been received.
                //
                g_ui32Flags |= COMMAND_RECEIVED;
                ui32CmdIdx++;

            }


            break;
        }

        //
        // We are being asked how much unprocessed data we have still to
        // process. We return 0 if the UART is currently idle or 1 if it is
        // in the process of transmitting something. The actual number of
        // bytes in the UART FIFO is not important here, merely whether or
        // not everything previously sent to us has been transmitted.
        //
        case USB_EVENT_DATA_REMAINING:
        {
            //
            // Get the number of bytes in the buffer and add 1 if some data
            // still has to clear the transmitter.
            //
            return(0);
        }

        //
        // We are being asked to provide a buffer into which the next packet
        // can be read. We do not support this mode of receiving data so let
        // the driver know by returning 0. The CDC driver should not be
        // sending this message but this is included just for illustration and
        // completeness.
        //
        case USB_EVENT_REQUEST_BUFFER:
        {
            return(0);
        }

        //
        // We don't expect to receive any other events.  Ignore any that show
        // up in a release build or hang in a debug build.
        //
        default:
        {
            break;
        }
    }

    return(0);
}

void setup_usb()
{

    uint32_t ui32PLLRate;
//    char cOutString[32];
//    char cOutString2[32];
//    char user_in[32];
#ifdef USE_ULPI
    uint32_t ui32ULPI;
#endif
    ui32CmdIdx = 0;

    //
    // Run from the PLL at 120 MHz.
    //
//    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
//                                             SYSCTL_OSC_MAIN |
//                                             SYSCTL_USE_PLL |
//                                             SYSCTL_CFG_VCO_480), 120000000);

    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_OSC_INT |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480), 120000000);

    //
    // Not configured initially.
    //
    g_bUSBConfigured = false;


    //
    // Enable the peripherals used in this example.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_USB0);

    //
    // Configure the device pins.
    //
    PinoutSet(false, true);



    //
    // Enable the system tick.
    //
    SysTickPeriodSet(g_ui32SysClock / SYSTICKS_PER_SECOND); // 120000000 / 100
    SysTickIntEnable();
    SysTickEnable();

    //
    // Initialize the transmit and receive buffers for first serial device.
    //
    USBBufferInit(&g_psTxBuffer);
    USBBufferInit(&g_psRxBuffer);

    //
    // Initialize the serial port
    //
    USBDCDCCompositeInit(0, &g_psCDCDevice, 0);

    //
    // Tell the USB library the CPU clock and the PLL frequency.
    //
//    SysCtlVCOGet(SYSCTL_XTAL_25MHZ, &ui32PLLRate);
    ui32PLLRate = 240000000;
    USBDCDFeatureSet(0, USBLIB_FEATURE_CPUCLK, &g_ui32SysClock);
    USBDCDFeatureSet(0, USBLIB_FEATURE_USBPLL, &ui32PLLRate);

#ifdef USE_ULPI
    //
    // Tell the USB library to use ULPI interface
    //
    ui32ULPI = USBLIB_FEATURE_ULPI_HS;
    USBDCDFeatureSet(0, USBLIB_FEATURE_USBULPI, &ui32ULPI);
#endif

    //
    // Initial serial device and pass the device information to the USB library and place the device
    // on the bus.
    //
    USBDCDCInit(0, &g_psCDCDevice);

}




/******************************************************
 *
 * Helper USB functions
 *
 *****************************************************/

/*
 * Sends the data on send_buff over the usb line. It write length bytes.
 */
void usb_send(uint8_t *send_buff, int length) {
    USBBufferWrite((tUSBBuffer *)&g_psTxBuffer, send_buff, length);
}

/*
 * Gets length bytes from the usb buffer and sticks it in get_buff.
 */
void usb_get(uint8_t *get_buff, int length) {
    buff_cpy(g_pcCmdBuf, get_buff, length);
}

/******************************************************
 *
 * Global variables
 *
 *****************************************************/

 // the id of the given device
uint8_t DAQ_ID = 0;

// (signal averaging factor) the number of times to measure on each node
uint8_t SAF = 0;

// the status of the device (see daq_functions.h)
uint8_t DAQ_STATUS = 0;

// the value of current to use
uint8_t CURR_VALUE = 0;

// the current firmware version
uint8_t FW_VERSION = 0x50;

// the injection pattern
struct inj_pair inj_pairs[NUM_NODES];
/**************************************************************************
 *
 * Polling (super loop) that handles the main functionality of the system.
 *
 **************************************************************************/


int main(void) {
    //
    // Main application loop.
    //
    setup_usb();

    // handshake part a and b
    int hs1_flag, hs2_flag;
    hs1_flag = hs2_flag = 0;

    // buffers to hold usb data
    uint8_t instr_in[MAX_PACKET_SIZE];
    uint8_t response_out[RESPONSE_SIZE];
    uint8_t hs_in[HS_SIZE];
    uint8_t hs_out[HS_SIZE];

    while(1)
    {
        //
        // Device has been enumerated by host
        //
        if(g_bUSBConfigured)
        {

            //
            if(g_ui32Flags & COMMAND_RECEIVED & ~COMMAND_TRANSMIT_COMPLETE)
            {

                // set interrupt flags
                g_ui32Flags &= ~COMMAND_RECEIVED & ~COMMAND_TRANSMIT_COMPLETE;

                // add usb data to desired buffer
                (hs1_flag && hs2_flag) ? usb_get(instr_in, MAX_PACKET_SIZE) : usb_get(hs_in, HS_SIZE);

                /* complete handshake:
                 *     host   -> 0xDE
                 *     device -> 0xEF
                 *     host   -> 0xDE
                 *     device -> 0xEF  */
                if(!hs1_flag && hs_in[0] == HS1_IN) {
                    hs_out[0] = HS1_OUT;
                    usb_send(hs_out, HS_SIZE);
                    hs1_flag = 1;
                    continue;
                }
                if(!hs2_flag && hs_in[0] == HS2_IN) {
                    hs_out[0] = HS2_OUT;
                    usb_send(hs_out, HS_SIZE);
                    hs2_flag = 1;
                    continue;
                }

                // start setting the values for the response packet
                response_out[RESPONSE_PREFIX] = instr_in[INSTR_PREFIX];
                response_out[RESPONSE_SUFFIX] = instr_in[INSTR_SUFFIX];
                response_out[RESPONSE_ID_INDX] = instr_in[INSTR_ID_INDX];

                // data and error have default value of zero
                response_out[RESPONSE_DATA_MSB] = response_out[RESPONSE_DATA_LSB] = response_out[RESPONSE_ERRORS] = 0;

                /* begin receiving instructions
                 *
                 * all cases share a similar structure:
                 *      - verify correct instruction suffix
                 *      - set the status of system (if it changed)
                 *      - respond to the host with either the current status or an error
                 *      - All but ID_SET instruction check that DAQ id is correct (SET_ID must always be first)
                 *
                 * instructions must come in in a certain order:
                 *      1) set DAQ ID
                 *      2) firmware version query
                 *      3) equivalent resistance query
                 *      4) set SAF
                 *      5) set current value
                 *      6) set current nodes pattern
                 *      7) set ground nodes pattern
                 *      8) start measurements
                 *
                 * however, get_status and sw_driven_reset can come at any time (after id has been set).
                 * furthermore, in the sequence above, instructions cannot occur before any of their proceeding instructions
                 * but after a given instruction has occurred, that instruction, as well as all of its proceeding instructions,
                 * are free to recur any number of times
                 *
                 * reset instruction reset the system back to a clean state with only a DAQ ID set
                 *
                 */
                switch(instr_in[INSTR_PREFIX]){
                    // daq id has to be set before anything can happen
                    case ID_SET_PRFX:
                        if (instr_in[INSTR_SUFFIX] == ID_SET_SUFX) {
                            DAQ_ID = instr_in[INSTR_ID_INDX];
                            DAQ_STATUS |= ID_SET;
                            response_out[RESPONSE_STATUS] = DAQ_STATUS;
                        }
                        else {
                            response_out[RESPONSE_ERRORS] = INVALID_INST_SFX;
                        }
                        usb_send(response_out, RESPONSE_SIZE);
                        break;
                    // host tells the system to reset itself (all except device id)
                    case SW_DRIVEN_RESET_PRFX:
                        if (!(instr_in[INSTR_ID_INDX] == DAQ_ID)) {
                            response_out[RESPONSE_ERRORS] = INVALID_DAQ_ID;
                        }
                        else
                        if (instr_in[INSTR_SUFFIX] == SW_DRIVEN_RESET_SUFX) {
                            if(DAQ_STATUS & ID_SET) {
                                DAQ_STATUS = ID_SET;
                            }
                            else {
                                response_out[RESPONSE_ERRORS] = INVALID_INST_ORDER;
                            }
                            response_out[RESPONSE_STATUS] = DAQ_STATUS;
                        }
                        else {
                            response_out[RESPONSE_ERRORS] = INVALID_INST_SFX;
                        }
                        usb_send(response_out, RESPONSE_SIZE);
                        break;
                    // host requests status of device
                    case STATUS_GET_PRFX:
                        if (!(instr_in[INSTR_ID_INDX] == DAQ_ID)) {
                            response_out[RESPONSE_ERRORS] = INVALID_DAQ_ID;
                        }
                        else
                        if (instr_in[INSTR_SUFFIX] == STATUS_GET_SUFX) {
                            response_out[RESPONSE_STATUS] = DAQ_STATUS;
                            if (!(DAQ_STATUS & ID_SET)) {
                                response_out[RESPONSE_ERRORS] = INVALID_INST_ORDER;
                            }
                        }
                        else {
                            response_out[RESPONSE_ERRORS] = INVALID_INST_SFX;
                        }
                        usb_send(response_out, RESPONSE_SIZE);
                        break;
                     // host requests the firmware version
                    case FW_VERSION_PRFX:
                        if (!(instr_in[INSTR_ID_INDX] == DAQ_ID)) {
                            response_out[RESPONSE_ERRORS] = INVALID_DAQ_ID;
                        }
                        else
                        if (instr_in[INSTR_SUFFIX] == FW_VERSION_SUFX) {
                           if(DAQ_STATUS & ID_SET) {
                               response_out[RESPONSE_DATA_LSB] = FW_VERSION;
                               DAQ_STATUS |= VERSION_RETRIEVED;
                           }
                           else {
                               response_out[RESPONSE_ERRORS] = INVALID_INST_ORDER;
                           }
                           response_out[RESPONSE_STATUS] = DAQ_STATUS;
                        }
                        else {
                            response_out[RESPONSE_ERRORS] = INVALID_INST_SFX;
                        }
                        usb_send(response_out, RESPONSE_SIZE);
                        break;
                    // host requests the equivalent resistance of the substrate
                    case EQUIV_RES_PRFX:
                        if (!(instr_in[INSTR_ID_INDX] == DAQ_ID)) {
                            response_out[RESPONSE_ERRORS] = INVALID_DAQ_ID;
                        }
                        else
                        if (instr_in[INSTR_SUFFIX] == EQUIV_RES_SUFX) {
                           if(DAQ_STATUS & VERSION_RETRIEVED) {
                               uint16_t equiv_res = 500; // dummy value until we get it working
                               // equiv_res =  get_equivalent_resistance();
                               response_out[RESPONSE_DATA_MSB] = equiv_res >> 8; // 0x1
                               response_out[RESPONSE_DATA_LSB] = equiv_res & 0xFF; // 0xF4
                               DAQ_STATUS |= RES_RETRIEVED;
                           }
                           else {
                               response_out[RESPONSE_ERRORS] = INVALID_INST_ORDER;
                           }
                           response_out[RESPONSE_STATUS] = DAQ_STATUS;
                        }
                        else {
                            response_out[RESPONSE_ERRORS] = INVALID_INST_SFX;
                        }
                        usb_send(response_out, RESPONSE_SIZE);
                        break;
                    // host sets the SAF value
                    case SAF_SET_PRFX:
                        if (!(instr_in[INSTR_ID_INDX] == DAQ_ID)) {
                            response_out[RESPONSE_ERRORS] = INVALID_DAQ_ID;
                        }
                        else
                        if (instr_in[INSTR_SUFFIX] == SAF_SET_SUFX) {
                           if(DAQ_STATUS & RES_RETRIEVED) {
                               SAF = instr_in[INSTR_DATA_LSB];
                               DAQ_STATUS |= SAF_SET;
                           }
                           else {
                               response_out[RESPONSE_ERRORS] = INVALID_INST_ORDER;
                           }
                           response_out[RESPONSE_STATUS] = DAQ_STATUS;
                        }
                        else {
                            response_out[RESPONSE_ERRORS] = INVALID_INST_SFX;
                        }
                        usb_send(response_out, RESPONSE_SIZE);
                        break;
                    // host sets current value
                    case CRNTV_SET_PRFX:
                        if (!(instr_in[INSTR_ID_INDX] == DAQ_ID)) {
                            response_out[RESPONSE_ERRORS] = INVALID_DAQ_ID;
                        }
                        else
                        if (instr_in[INSTR_SUFFIX] == CRNTV_SET_SUFX) {
                            if(DAQ_STATUS & SAF_SET) {
                                CURR_VALUE = instr_in[INSTR_DATA_LSB];
                                DAQ_STATUS |= CRNTV_SET;
                            }
                            else {
                                response_out[RESPONSE_ERRORS] = INVALID_INST_ORDER;
                            }
                            response_out[RESPONSE_STATUS] = DAQ_STATUS;
                        }
                        else {
                            response_out[RESPONSE_ERRORS] = INVALID_INST_SFX;
                        }
                        usb_send(response_out, RESPONSE_SIZE);
                        break;
                    // host sets the injection pattern (the current nodes in order)
                    case CRNT_PTRN_SET_PRFX:
                        if (!(instr_in[INSTR_ID_INDX] == DAQ_ID)) {
                            response_out[RESPONSE_ERRORS] = INVALID_DAQ_ID;
                        }
                        else
                        if (instr_in[INJ_PTRN_SUFFIX] == CRNT_PTRN_SET_SUFX) {
                            if(DAQ_STATUS & CRNTV_SET) {
                                uint8_t i;
                                for (i = 0; i < NUM_NODES; i++) {
                                    inj_pairs[i].curr = instr_in[i + INJ_PTRN_BIT0];
                                }
                                DAQ_STATUS |= CRNT_PTRN_SET;
                            }
                            else {
                                response_out[RESPONSE_ERRORS] = INVALID_INST_ORDER;
                            }
                            response_out[RESPONSE_STATUS] = DAQ_STATUS;
                        }
                        else {
                            response_out[RESPONSE_ERRORS] = INVALID_INST_SFX;
                        }
                        usb_send(response_out, RESPONSE_SIZE);
                        break;
                    // host sets the injection pattern (the ground nodes in order)
                    case GND_PTRN_SET_PRFX:
                        if (!(instr_in[INSTR_ID_INDX] == DAQ_ID)) {
                            response_out[RESPONSE_ERRORS] = INVALID_DAQ_ID;
                        }
                        else
                        if (instr_in[INJ_PTRN_SUFFIX] == GND_PTRN_SET_SUFX) {
                            if(DAQ_STATUS & CRNT_PTRN_SET) {
                                uint8_t i;
                                for (i = 0; i < NUM_NODES; i++) {
                                    inj_pairs[i].gnd = instr_in[i + INJ_PTRN_BIT0];
                                }
                                DAQ_STATUS |= GND_PTRN_SET;
                            }
                            else {
                                response_out[RESPONSE_ERRORS] = INVALID_INST_ORDER;
                            }
                            response_out[RESPONSE_STATUS] = DAQ_STATUS;
                        }
                        else {
                            response_out[RESPONSE_ERRORS] = INVALID_INST_SFX;
                        }
                        usb_send(response_out, RESPONSE_SIZE);
                        break;
                    // host tells the sytem to start taking measurements
                    case START_MEAS_PRFX:
                        if (!(instr_in[INSTR_ID_INDX] == DAQ_ID)) {
                            response_out[RESPONSE_ERRORS] = INVALID_DAQ_ID;
                        }
                        else
                        if (instr_in[INSTR_SUFFIX] == START_MEAS_SUFX) {
                            if(DAQ_STATUS & GND_PTRN_SET) {
                                // call measurement function
                            }
                            else {
                                response_out[RESPONSE_ERRORS] = INVALID_INST_ORDER;
                            }
                            response_out[RESPONSE_STATUS] = DAQ_STATUS;
                        }
                        else {
                            response_out[RESPONSE_ERRORS] = INVALID_INST_SFX;
                        }
                        usb_send(response_out, RESPONSE_SIZE); // send response packet
                        // send measurement data as well
                        break;
                    default:
                    {
                        // the instruction prefix wasn't recognized
                        response_out[RESPONSE_ERRORS] = INVALID_INST_PFX;
                        usb_send(response_out, RESPONSE_SIZE);
                    }
                }
            }
        }
    }
}

