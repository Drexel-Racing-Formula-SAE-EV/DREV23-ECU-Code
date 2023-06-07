/**
 * @file canbus_task.c
 * @author Cole Bardin (cab572@drexel.edu)
 * @brief 
 * @version 0.1
 * @date 2023-04-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "tasks/canbus_task.h"
#include "ext_drivers/canbus.h"

/**
 * @brief CANBus task function
 * 
 * @param arg App_data struct pointer converted to void pointer
 */
void canbus_task_fn(void *arg);

TaskHandle_t canbus_task_start(struct app_data *data) {
    TaskHandle_t handle;
    xTaskCreate(canbus_task_fn, "CANBus Task", 128, (void *)data, 8, &handle);
    return handle;
}

void canbus_task_fn(void *arg) {
    struct app_data *data = (struct app_data *)arg;

    struct canbus_device *canbus_device = &data->board.canbus_device;
    CAN_HandleTypeDef *hcan = canbus_device->hcan;
    CAN_TxHeaderTypeDef *tx_header = data->board.canbus_device.tx_header;
    osMessageQueueId_t canbus_mq = data->board.stm32f767.can1_mq;
    canbus_packet tx_packet;

    osStatus_t status;
    uint8_t tx_data[8] = {0};

    while(1) {
        xTaskNotifyWait(0, 0, NULL, HAL_MAX_DELAY);
        status = osMessageQueueGet(canbus_mq, &tx_packet, NULL, HAL_MAX_DELAY);
        if(status == osOK){
            for(uint8_t i = 0; i < 8; i++){
                tx_data[i] = tx_packet.tx_data[i];
            }
            tx_header->StdId = tx_packet.tx_id;
            HAL_CAN_AddTxMessage(hcan, tx_header, tx_data, &canbus_device->tx_mailbox);
        }
    }
}

