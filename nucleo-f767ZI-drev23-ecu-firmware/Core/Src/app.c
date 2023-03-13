#include "app.h"

void app_create(struct app_data* data) {
    data->system_shutdown = true;

    data->rtd_flag = false;
    data->torque = 0;
}