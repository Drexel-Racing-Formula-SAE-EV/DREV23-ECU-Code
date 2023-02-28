/*
 * poten.c
 *
 *  Created on: Feb 27, 2023
 *      Author: colebardin
 */
#include <poten/poten.h>
#include <math.h>

#define THRESH 10
#define NSAMPLES 100

void poten_init(struct poten *poten, uint16_t min, uint16_t max) {
	poten->min = min;
	poten->max = max;
}

// Parsed from Arduino's Wiring.h
long map(long x, long in_min, long in_max, long out_min, long out_max) {
	long in_range = in_max - in_min;
	long out_range = out_max - out_min;
	if (in_range == 0) return out_min + out_range / 2;
	long num = (x - in_min) * out_range;
	if (out_range >= 0) {
		num += in_range / 2;
	} else {
		num -= in_range / 2;
	}
	long result = num / in_range + out_min;
	if (out_range >= 0) {
		if (in_range * num < 0) return result - 1;
	} else {
		if (in_range * num >= 0) return result + 1;
	}
	return result;
}

short adc_raw_to_percent(struct poten *root, uint16_t raw) {
	return map(raw, root->min, root->min, 0, 100);
}

uint16_t percent_to_trq_hex(short percent){
    if (percent > 100) percent = 100;
    if (percent < 0) percent = 0;
	return map(percent, 0, 100, 0x0000, 0x5555);
}

uint8_t check_implausability(short L, short R)
{
    static unsigned int counts;
    // Count number of reoccuring instances of torque values differing more than THRESH %
    if (abs(L-R) > THRESH){
        counts++;
        if (counts >= NSAMPLES){
            // Prolonged Implausibililty detected, stop car
        	//Set RFE Low
        	return 0;
        }
    } else {
        counts = 0;
        return 1;
    }
}
