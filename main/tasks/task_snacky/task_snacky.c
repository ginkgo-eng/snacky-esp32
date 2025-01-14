#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "task_snacky.h"
#include "esp_log.h"
//#include "unity.h"
//#include "unity_test_runner.h"
//#include "esp_heap_caps.h"
//#include "test_utils.h"

#define STACK_SIZE (2048)

void task_snacky(void * pvParameters);

static const char * TAG = "Snack";

void task_snacky_init()
{
    BaseType_t ret;
    TaskHandle_t task_snacky_handle = NULL;
    ret = xTaskCreate(task_snacky, "TASK_SNACKY", STACK_SIZE, NULL, 1, &task_snacky_handle);
    
    if (ret == pdPASS)
    {
        vTaskDelete( task_snacky_handle );
    }


    // asserts?
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
