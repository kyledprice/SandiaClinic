/*
 * usb_functions.c
 *
 *  Created on: Jan 29, 2019
 *      Author: kyleprice
 */

#include "usb_functions.h"


/*
 * Simply copy a given amount of a buffer.
 *
 */
void buff_cpy(char *src, uint8_t *dest, int length) {
    int i;
    for(i = 0; i < length; i++) {
        dest[i] = src[i];
    }
}




