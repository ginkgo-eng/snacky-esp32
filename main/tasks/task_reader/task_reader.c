#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "task_config.h"

#include "task_reader.h"

void task_reader_init()
{
        // Create Queues
        xQueueCreate(DEFAULT_QUEUE_LENGTH, sizeof(uint8_t));

        // Create Task
        BaseType_t ret;
        TaskHandle_t task_reader_handle = NULL;
        ret = xTaskCreate(task_reader, "TASK_READER", DEFAULT_TASK_STACK_SIZE, NULL, 1, &task_reader_handle);
    
        // If sucessful, delete the task and exit gracefully.
        if (ret == pdPASS)
        {
            vTaskDelete( task_reader_handle );
        }
}

void task_reader();

void task_reader_deinit();

