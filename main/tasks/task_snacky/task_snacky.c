#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
//#include "unity.h"
//#include "unity_test_runner.h"
//#include "esp_heap_caps.h"
//#include "test_utils.h"
#include "task_config.h"

#include "task_snacky.h"

static const char * TAG = "Snack";

void task_snacky_init()
{
    // Create Queues
    xQueueCreate(DEFAULT_QUEUE_LENGTH, sizeof(uint8_t));

    // Create Task
    BaseType_t ret;
    TaskHandle_t task_snacky_handle = NULL;
    ret = xTaskCreate(task_snacky, "TASK_SNACKY", DEFAULT_TASK_STACK_SIZE, NULL, 1, &task_snacky_handle);

    
    // If sucessful, delete the task and exit gracefully.
    if (ret == pdPASS)
    {
        vTaskDelete( task_snacky_handle );
    }
}

void task_snacky(void * pvParameters)
{
    for(;;)
    {
        ESP_LOGI(TAG, "HI");
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

void task_snacky_deinit(TaskHandle_t task_snacky_handle)
{
    vTaskDelete(task_snacky_handle);
}
