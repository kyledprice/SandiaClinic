#include "ti/devices/msp432e4/driverlib/driverlib.h"


/************************************************************
* HANDSHAKE
************************************************************/
#define HS_SIZE                 1
#define HS1_IN                  0xDE
#define HS1_OUT                 0xAD
#define HS2_IN                  0xBE
#define HS2_OUT                 0xEF

/************************************************************
* INSTRUCTION PACKET DETAILS
************************************************************/
#define INSTR_SIZE                    5
#define INSTR_PREFIX                  0
#define INSTR_ID_INDX                 1
#define INSTR_DATA_MSB                2
#define INSTR_DATA_LSB                3
#define INSTR_SUFFIX                  4

/************************************************************
* INJECTION PATTERN PACKET DETAILS
************************************************************/
#define MAX_PACKET_SIZE               35
#define INJ_PTRN_SIZE                 35
#define INJ_PTRN_PREFIX               0
#define INJ_PTRN_ID_INDX              1
#define INJ_PTRN_BIT0                 2
#define INJ_PTRN_SUFFIX               34

/************************************************************
* RESPONSE PACKET DETAILS
************************************************************/
#define RESPONSE_SIZE                 7
#define RESPONSE_PREFIX               0
#define RESPONSE_ID_INDX              1
#define RESPONSE_STATUS               2
#define RESPONSE_DATA_MSB             3
#define RESPONSE_DATA_LSB             4
#define RESPONSE_ERRORS               5
#define RESPONSE_SUFFIX               6

/************************************************************
* ERROR CODES
************************************************************/
#define INVALID_INST_SFX              0x01
#define INVALID_INST_ORDER            0x02
#define INVALID_DAQ_ID                0x03
#define INVALID_INST_PFX              0x04

/************************************************************
* USB PACKET PREFIXES AND SUFFIXES
************************************************************/

// This instruction package directly changes the DAQ ID of the device
#define ID_SET_PRFX             0xFA
#define ID_SET_SUFX             0xEA

// Define the package prefix and suffix for the signal averaging factor (SAF - the number of times the
// the measurements are taken on each node) package
#define SAF_SET_PRFX            0xAC
#define SAF_SET_SUFX            0xBC

//Define the package prefix and suffix for SET CURRENT VALUE packages (from host)
#define CRNTV_SET_PRFX          0xCE
#define CRNTV_SET_SUFX          0xFF

// Define the package prefix and suffix for current nodes package
#define CRNT_PTRN_SET_PRFX      0xCC
#define CRNT_PTRN_SET_SUFX      0xDD

// Define the package prefix and suffix for ground nodes package
#define GND_PTRN_SET_PRFX       0xCD
#define GND_PTRN_SET_SUFX       0xDF

//Define the package prefix and suffix for STATUS packages
#define STATUS_GET_PRFX         0xAE
#define STATUS_GET_SUFX         0xAF

//Define the package prefix and suffix for outgoing measured DATA packages
#define DATA_PRFX               0xBE
#define DATA_SUFX               0xEF

//Define the package prefix and suffix for firmware version request
#define FW_VERSION_PRFX         0xCF
#define FW_VERSION_SUFX         0xCB

//Define the package prefix and suffix for equivalent resistance calculation
#define EQUIV_RES_PRFX          0xAA
#define EQUIV_RES_SUFX          0xAB

//Define the package prefix and suffix for software driven reset
#define SW_DRIVEN_RESET_PRFX    0xFC
#define SW_DRIVEN_RESET_SUFX    0xFD

// start measurement packet
#define START_MEAS_PRFX         0xFE
#define START_MEAS_SUFX         0xEB

/*
 * Simply copy a given amount of a buffer.
 *
 */
void buff_cpy(char *src, uint8_t *dest, int lenth);
