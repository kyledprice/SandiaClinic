/*****************************************************************************
*
* Copyright (C) 2013 - 2017 Texas Instruments Incorporated - http://www.ti.com/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* * Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the
*   distribution.
*
* * Neither the name of Texas Instruments Incorporated nor the names of
*   its contributors may be used to endorse or promote products derived
*   from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*
* MSP432 empty main.c template
*
******************************************************************************/

#include "msp.h"
#include "curr_source_control.h"
#include "projection_cont.h"
//#include "adc.h"


void test_curr_source() {
    // Should rotate through all the different current source values.
    volatile int i = 1, j = 0;
    curr_source_init();
    while(1) {
        curr_source_set(i);
        for(j = 0; j < 20000000; j++);
        i += 20;
        i = i % 100;
    }
}

void test_proj_cont() {
    // Switch projection pins
    volatile int i = 0, j = 0;
    proj_init();
    while(1) {
        current_proj_set(i);
        gnd_proj_set(i+1);
        for(j = 0; j < 20000000; j++);
        i++;
        i = i % 17;
    }
}

int main(void)
{
	// Change this number to select which of the tests will be run.
	// 0 switches through all the current values in an infinite loop and outputs them through a single projection locaiton. Don't use at the moment.
	// 1 switches between all the projection nodes with a set current value.
	// 2 tests an individual current and projection node. For initial testing leave this value at 2.
    int test = 2;
	
	// Sets which node the current should be set to for test 2. Make sure current and ground are never set to the same node or things will be shorted out.
	int curr_node = 1;
	
	// Set which node the ground should be set to for test 2. Make sure current and ground are never set to the same node or things will be shorted out.
	int gnd_node = 2;
	
	// Sets the desired current value. The current is set in increments of 10 micro amps with 1 = 10 micro, 2 = 20 micro, 10 = 100 micro, ect. 
	int curr= 10;
	
    switch(test) {
        case 0:
            test_curr_source();
            break;
        case 1:
            test_proj_cont();
            break;
        case 2:
			// We still have not gotten the switches to work so only test one set at a time. You must always call proj_init(). But you can switch
			// whether you want to set the current or ground node by changing this value to 1 or 0. It is preset to 1 which is what we where testing on 
			// Saturday. For a quick initial test leave it a 1. Leave the current source code commented out for the moment.
            int which_proj = 1;
			
			proj_init();
			if (which_proj == 0) {
				current_proj_set(curr_node);
			}
            else {
				gnd_proj_set(gnd_node);
			}
            //curr_source_init();
            //curr_source_set(curr);
            while(1);
        default:
            break;
    }
    return 0;
}
