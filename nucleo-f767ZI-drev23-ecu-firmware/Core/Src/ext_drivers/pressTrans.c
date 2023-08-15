/*
 * pressTrans.c
 *
 *  Created on: Apr 24, 2023
 *      Author: Benedict Hofmockel
 */
#include <ext_drivers/pressTrans.h>
#include <ext_drivers/map.h>
#include <math.h>

//#include "main.h" //added because switch Channel function

#define THRESH 10
#define NSAMPLES 100

void pressTrans_init(struct pressTrans *pressTrans,
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

float presstrans_raw_to_percent(struct pressTrans *root, uint16_t raw) {
	float percent = (float)map(raw, root->min, root->max, 0, 100);
	if(percent > 100.0){
		return 100.0;
	}else if(percent < 0.0){
		return 0.0;
	}else{
		return percent;
	}
}

uint8_t presstrans_check_implausability(short L,
							short R){
    static unsigned int counts = 0;
    // Count number of reoccuring instances of torque values differing more than THRESH %
    if ( (fabs(L-R) > THRESH) && (++counts >= NSAMPLES) ){
            // Prolonged Implausibililty detected, stop car
	return 1; //TODO:  rewrite this function for BSE from prefeature APPS b
        	//Set RFE Low
        	return 0;
    }
	counts = 0;
	return 1;
}

uint8_t switch_to_defined_channel (struct pressTrans *root){
	//TODO: add code here from the prefeature APPS branch
	ADC_ChannelConfTypeDef sConfig = {0};
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = root->channelNum;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(root->handle, &sConfig) != HAL_OK)
	{
//		Error_Handler(); //Ben currently has no clue what this does
		return HAL_ERROR;
	} else {
		return HAL_OK;
	}
}


