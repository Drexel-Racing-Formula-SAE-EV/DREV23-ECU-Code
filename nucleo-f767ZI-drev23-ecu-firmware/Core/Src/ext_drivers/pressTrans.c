/*
 * pressTrans.c
 *
 *  Created on: Apr 24, 2023
 *      Author: Benedict Hofmockel
 */
#include <ext_drivers/pressTrans.h>
#include <math.h>

//#include "main.h" //added because switch Channel function

#define THRESH 10
#define NSAMPLES 100

void pressTransduc_init(struct pressTrans *pressTrans,
					uint16_t min,
					uint16_t max,
					void *handle,
					uint8_t channelNum,
					uint16_t(*read_count)(void *arg)) {
	pressTrans->min = min;
	pressTrans->max = max;
	pressTrans->handle = handle;
	pressTrans->channelNum = channelNum;
	pressTrans->read_count = read_count;
}

// Parsed from Arduino's Wiring.h
long map(long x,
		long in_min,
		long in_max,
		long out_min,
		long out_max) {
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

//short adc_raw_to_percent(struct pressTrans *root,
//		uint16_t raw) {
//	return (short)map(raw, root->min, root->min, 0, 100);
//}

uint16_t percent_to_trq_hex(short percent){ //TODO:  rename and rewrite this function for BSE from prefeature APPS branch fork
    if (percent > 100) percent = 100;
    if (percent < 0) percent = 0;
	return map(percent, 0, 100, 0x0000, 0x5555);
}

uint8_t check_implausability(short L,
							short R){
    static unsigned int counts = 0;
    // Count number of reoccuring instances of torque values differing more than THRESH %
    if ( (fabs(L-R) > THRESH) && (++counts >= NSAMPLES) ){
            // Prolonged Implausibililty detected, stop car
        	//Set RFE Low
        	return 0;
    }
	counts = 0;
	return 1; //TODO:  rewrite this function for BSE from prefeature APPS branch fork
}

uint8_t switch_to_defined_channel (struct pressTrans *root){
	//TODO: add code here from the prefeature APPS branch
	ADC_ChannelConfTypeDef sConfig = {0};
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = root->channelNum;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&root->handle, &sConfig) != HAL_OK)
	{
		return 1;
//		Error_Handler(); //Ben currently has no clue what this does
	} else {
		return 0;
	}
}


