/**
 * @file apps_task.c
 * @author Cole Bardin (cab572@drexel.edu)
 * @brief
 * @version 0.1
 * @date 2023-04-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "main.h"
#include "tasks/apps_task.h"
#include "ext_drivers/canbus.h"

#define TRQ_HEX_TO_LSB(x) (x & 0xff)
#define TRQ_HEX_TO_MSB(x) (x >> 8)

/**
 * @brief Actual APPS task function
 *
 * @param arg App_data struct pointer converted to void pointer
 */
void apps_task_fn(void *arg);

TaskHandle_t apps_task_start(struct app_data *data) {
    TaskHandle_t handle;
    xTaskCreate(apps_task_fn, "APPS task", 128, (void *)data, 7, &handle);
    return handle;
}

void apps_task_fn(void *arg) {
    struct app_data *data = (struct app_data *)arg;
    struct poten *apps1 = &data->board.apps1;
    struct poten *apps2 = &data->board.apps2;

    uint16_t adc_raw[2];
    float throttle_percent[2];
    float avg_throttle;
    uint16_t torque_hex;
    canbus_packet tx_packet;
    uint32_t entryTicksCount;

    // Initialize all CANBus data values to 0
    for (uint8_t i = 0; i < 8; i++){
        tx_packet.data[i] = 0x00;
    }

    // Set CANBus Receiving ID in header
    tx_packet.id = BAMOCAR_CANBUS_RXID;
    // Set the command identifier to be Torque Command
    tx_packet.data[0] = BAMOCAR_CANBUS_TORQUE_CMD;

    osMessageQueueId_t canbus_mq = data->board.stm32f767.can1_mq;

    while (1)
    {
        // Record number of ticks at entry of each loop 
        entryTicksCount = osKernelGetTickCount();

        if(data->rtd_flag == false){
            // Read APPS potentiometers
            adc_raw[0] = apps1->read_count((void *)apps1);
            adc_raw[1] = apps2->read_count((void *)apps2);

            // Convert to a floating point percentage
            throttle_percent[0] = adc_raw_to_percent(apps1, adc_raw[0]);
            throttle_percent[1] = adc_raw_to_percent(apps2, adc_raw[1]);

            if(!check_implausability(throttle_percent[0], throttle_percent[1])){
                // If plausibility check fails, set flag until soft reset
                data->rtd_flag = true;
                // Set RFE low, disable motor
                HAL_GPIO_WritePin(BAMOCAR_RFE_Activate_GPIO_Port, BAMOCAR_RFE_Activate_Pin, 0);
            }

            // Average throttle percents
            avg_throttle = (throttle_percent[0] + throttle_percent[1]) / 2;
            data->torque = avg_throttle;
            // Convert to hex number for Bamocar register value
            torque_hex = percent_to_trq_hex(avg_throttle);

            // When flag is not set, send normal torque command
            tx_packet.data[1] = TRQ_HEX_TO_LSB(torque_hex);
            tx_packet.data[2] = TRQ_HEX_TO_MSB(torque_hex);
        }else{
            // If implausibility is detected, send 0 torque command 
            tx_packet.data[1] = 0x00;
            tx_packet.data[2] = 0x00;
        }

        // Put torque packet in the queue and notify CANBus task
        osMessageQueuePut(canbus_mq, &tx_packet, 0, HAL_MAX_DELAY);
        xTaskNotify(data->canbus_task, CANBUS_APPS, eSetBits);

        // Delay such that this task will occur at exactly desired frequency
        osDelayUntil(entryTicksCount + (1000 / APPS_FREQ));
    }
}
