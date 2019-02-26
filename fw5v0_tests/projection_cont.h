/*
 * projection_cont.h
 *
 *  Created on: Feb 19, 2019
 *      Author: Skyler Swearngin
 */

#ifndef PROJECTION_CONT_H_
#define PROJECTION_CONT_H_

#include <stdint.h>
#include <stdbool.h>


/******************************************************************************
 *                               Initiation                                   *
 ******************************************************************************/
extern void current_proj_init();
extern void gnd_proj_init();
extern void proj_init();

/******************************************************************************
 *                                 Reset                                      *
 ******************************************************************************/
extern void current_proj_reset();
extern void gnd_proj_reset();
extern void proj_reset();

/******************************************************************************
 *                                 Control                                    *
 ******************************************************************************/
extern void current_proj_set(uint32_t node);
extern void gnd_proj_set(uint32_t node);

#endif /* PROJECTION_CONT_H_ */
