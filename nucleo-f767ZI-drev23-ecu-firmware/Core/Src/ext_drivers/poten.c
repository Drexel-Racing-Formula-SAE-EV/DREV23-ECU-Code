/*
 * poten.c
 *
 *  Created on: Mar 14, 2023
 *      Author: colebardin
 */
#include <ext_drivers/poten.h>
#include <math.h>

void poten_init(struct poten *poten, uint16_t min, uint16_t max, void *handle, uint16_t(*read_count)(void *arg)) {
	poten->min = min;
	poten->max = max;
	poten->handle = handle;
	poten->read_count = read_count;
}

// Parsed from Arduino's Wiring.h
long double map(long x, long in_min, long in_max, long out_min, long out_max) {
	long in_range = in_max - in_min;
	long out_range = out_max - out_min;
	if (in_range == 0) return out_min + (long double)out_range / 2;
	long double num = (x - in_min) * out_range;
	if (out_range >= 0) {
		num += (long double)in_range / 2;
	} else {
		num -= (long double)in_range / 2;
	}
	long double result = num / (long double)in_range + out_min;
	if (out_range >= 0) {
		if (in_range * num < 0) return result - 1;
	} else {
		if (in_range * num >= 0) return result + 1;
	}
	return result;
}
float adc_raw_to_percent(struct poten *root, uint16_t raw) {
	float percent = (float)map(raw, root->min, root->max, 100, 0);
	if(percent > 100.0){
		return 100.0;
	}else if(percent < 0.0){
		return 0.0;
	}else{
		return percent;
	}
}

uint16_t percent_to_trq_hex(float percent){
    if (percent > 100) percent = 100.0;
    if (percent < 0) percent = 0.0;
    return (uint16_t)percent * 0x5555;
}

uint8_t check_implausability(float L, float R)
{
    static unsigned int counts = 0;
    // Count number of reoccuring instances of torque values differing more than THRESH %
    if ( (fabs(L-R) > THRESH) && (++counts >= (100 / APPS_FREQ)) ){
            // Prolonged Implausibililty detected, stop car
        	//Set RFE Low
        	return 0;
    }
	counts = 0;
	return 1;
}

