#ifndef TASK_SNACKY_H
#define TASK_SNACKY_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

typedef enum
{
    SnackyInEvent_None = 0
} SnackyInEvent_e;

void task_snacky_init(void);
void task_snacky(void * pvParameters);
void task_snacky_deinit(TaskHandle_t task_snacky_handle);

#endif
