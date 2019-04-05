/*
 * instructions.h
 *
 *  Contains definitions for all the instructions used for communication between
 *  the software and the firmware.
 *
 *  Created on: Jan 15, 2019
 *      Author: Skyler Swearngin and Kyle Price
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

/*
 * The possible statuses for the daq.
 */
const int NOT_READY = 0x00;
const int CRNTV_SET = 0x01;
const int CRNTN_SET = 0x02;
const int GRND_SET = 0x04;
const int DAQID_SET = 0x08;
const int SAF_SET = 0x10;
const int START_SET = 0x20;

/*
 * Prefix and Suffix for set status package
 */
const int STATUS_SET_PRFX = 0xFA;
const int STATUS_SET_SUFX = 0xEA;

/*
 * Set current packet prefix and suffix
 */
const int CRNTN_SET_PRFX = 0xCC;
const int CRNTN_SET_SUFX = 0xDD;

/*
 * Set ground prefix and suffix
 */
const int GRNDN_SET_PRFX = 0xCD;
const int GRNDN_SET_SUFX = 0xFF;

/*
 * set current value packet suffix/prefix
 */
const int CRNTV_SET_PRFX = 0xCE;
const int CRNTV_SET_SUFX = 0xFF;

/*
 * get current value packet suffix/prefix
 */
const int CRNTV_GET_PRFX = 0xBF;
const int CRNTV_GET_SUFX = 0xCA;

/*
 * set the number of repetitions packet suffix/prefix
 */
const int SAF_SET_PRFX = 0xAC;
const int SAF_SET_SUFX = 0xBC;

/*
 * data packets suffix/prefix
 */
const int DATA_PRFX = 0xBE;
const int DATA_SUFX = 0xEF;

/*
 * start measurement packet
 */
const int START_PRFX = 0xFE;
const int START_SUFX = 0xEB;

/*
 * prefix/suffix for retrieving a daq's status
 */
const int STATUS_GET_PRFX = 0xAE;
const int STATUS_GET_SUFX = 0xAF;

/*
 * prefix/suffix for retrieving a daq's firmware version
 */
const int FW_VERSION_PRFX = 0xCF;
const int FW_VERSION_SUFX = 0xCB;

/*
 * prefix/suffix for retrieving substrates equivalent resistance
 */
const int EQUIV_RES_PRFX = 0xAA;
const int EQUIV_RES_SUFX = 0xAB;

/*
 * prefix/suffix for triggering a software driven reset
 */
const int SW_DRIVEN_RESET_PRFX = 0xFC;
const int SW_DRIVEN_RESET_SUFX = 0xFD;

#endif /* INSTRUCTIONS_H_ */
