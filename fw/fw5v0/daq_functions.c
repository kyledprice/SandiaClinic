/*
 * daq_functions.c
 *
 *  Created on: Mar 22, 2019
 *      Author: Skyler Swearngin
 */

#include "daq_functions.h"
#include "adc.h"
#include "curr_source_control.h"

/*
 * The function that handles all the set up and initialization to run
 * all the measurements. It will then take all the measurements needed and
 * store the data on board.
 * Parameters: curr - The target current value.
 *             saf - The desired signal averaging factor.
 *             data - An array where all the results will be stored.
 *             inj_pairs - The injection pair patterns measurements will be taken in.
 *             sys_clock - The speed the system clock is running at.
 */
void measure(uint8_t curr, uint8_t saf, uint16_t* data, struct inj_pair* inj_pairs, uint32_t sys_clock) {

    int node, meas_node, i;
    uint16_t temp_data1 = 0;
    uint16_t temp_data2 = 0;
    // Perform all the set up needed to call all the functions.
    proj_init();
    curr_source_init();
    ADC_node_init();
    configure_ADCs(sys_clock);

    // Set up the current value to be used for the whole process.
    curr_source_set(curr);

    // Start the measurement process.
    // First loop to switch through the projection patterns.
    for(node = 0; node < NUM_NODES; node++) {
        current_proj_set(inj_pairs[node].curr);
        gnd_proj_set(inj_pairs[node].gnd);
        // Delay as needed for the current to settle

        // Second loop through all the ADC's measurements
        set_ADC_1_2_node(1);
        for(meas_node = 0; meas_node < NUM_MEAS_NODES; meas_node++) {
            // Set first two nodes wait a little, set the second, 2 and measure the first 2.
            // Set first two to there next location, wait a second and measure the second.
            // Repeat the process.
            //set_ADC_1_2_node(measure_node+1);
            set_ADC_3_4_node(meas_node+1);
            SysCtlDelay(10);
            // Loop the measurements for the SAF
            for(i = 0; i < saf; i++) {
                temp_data1 += measure_ADC2();
                temp_data2 += measure_ADC1();
                // Add any delay that is desired here.
            }

            // Average out the data and store it in the provided array.
            temp_data1 /= saf;
            temp_data2 /= saf;

            data[meas_node] = temp_data1;
            data[meas_node+ADC1_OFFSET] = temp_data2;

            // Reset the temp data
            temp_data1 = 0;
            temp_data2 = 0;

            // Set the next measurement nodes.
            set_ADC_1_2_node(meas_node+2);

            // Add any additional delay required for the second adcs to settle here.
            // Repeat the above for the second set of adcs.
            for(i = 0; i < saf; i++) {
                temp_data1 += measure_ADC4();
                temp_data2 += measure_ADC3();
                // Add any needed delay between measurements here.
            }

            // Average out and store the data in the array.
            temp_data1 /= saf;
            temp_data2 /= saf;

            data[(meas_node+ADC4_OFFSET)*node] = temp_data1;
            data[(meas_node+ADC3_OFFSET)*node] = temp_data2;

            // Reset the temp data
            temp_data1 = 0;
            temp_data2 = 0;

            // Repeat the loop
        }
        // Loop.
    }
}

