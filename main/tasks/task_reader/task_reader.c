#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "task_reader.h"

void task_reader_init()
{
        // Create Queues
        xQueueCreate();

        // Create Task
        BaseType_t ret;
        TaskHandle_t task_reader_handle = NULL;
        ret = xTaskCreate(task_reader, "TASK_READER", STACK_SIZE, NULL, 1, &task_reader_handle);
    
        // If sucessful, delete the task and exit gracefully.
        if (ret == pdPASS)
        {
            vTaskDelete( task_reader_handle );
        }
}

void task_reader();

void task_reader_deinit();

