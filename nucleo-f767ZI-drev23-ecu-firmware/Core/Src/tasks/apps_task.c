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
    short throttle_percent[2];
    short avg_throttle;
    uint16_t torque_hex;
    canbus_packet tx_packet;

    for (uint8_t i = 0; i < 8; i++){
        tx_packet.tx_data[i] = 0x00;
    }

    tx_packet.tx_id = 0x201; // bamocar tx addr. use macros!!
    tx_packet.tx_data[0] = 0x90; // torque cmd

    osMessageQueueId_t canbus_mq = data->board.stm32f767.can1_mq;

    while (1)
    {
        adc_raw[0] = apps1->read_count((void *)apps1);
        adc_raw[1] = apps2->read_count((void *)apps2);

        throttle_percent[0] = adc_raw_to_percent(apps1, adc_raw[0]);
        throttle_percent[1] = adc_raw_to_percent(apps2, adc_raw[1]);

        // TODO: Check plausibilty

        avg_throttle = (throttle_percent[0] + throttle_percent[1]) / 2;
        data->torque = avg_throttle;
        torque_hex = percent_to_trq_hex(avg_throttle);

        tx_packet.tx_data[1] = TRQ_HEX_TO_LSB(torque_hex);
        tx_packet.tx_data[2] = TRQ_HEX_TO_MSB(torque_hex);

        osMessageQueuePut(canbus_mq, &tx_packet, 0, HAL_MAX_DELAY);
        xTaskNotify(data->canbus_task, 0, 0);

        osDelay(100);
    }
}
