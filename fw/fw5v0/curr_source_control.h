/*
 * curr_sourse_control.h
 *
 *  Created on: Jan 15, 2019
 *      Author: Skyler Swearngin
 */
#ifndef CURR_SOURCE_CONTROL_H_
#define CURR_SOURCE_CONTROL_H_

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 *                               Initialization                               *
 ******************************************************************************/
extern void curr_source_init();
extern void curr_source_reset();

/******************************************************************************
 *                              Selection                                     *
 ******************************************************************************/

/*
 * Sets the current source to provided the desired amount of current;
 * The Value is the desired current in microamps.
 */
extern void curr_source_set(uint32_t value);
extern void curr_source_set_microtens(uint32_t value);
extern void curr_source_set_microhunds(uint32_t value);
extern void curr_source_set_milliones(uint32_t value);
extern void curr_source_set_millitens(uint32_t value);

#endif /* CURR_SOURCE_CONTROL_H_ */
