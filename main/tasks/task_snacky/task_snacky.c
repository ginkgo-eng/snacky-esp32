#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "task_config.h"

#include "task_snacky.h"

static const char * TAG = "Snacky";

typedef struct SnackyCtrl_s 
{
    TaskHandle_t    task_handle;
} SnackyCtrl_t;

// --- Local Variables

static SnackyCtrl_t * snackyCtrl = NULL;

// --- Functions

void task_snacky_init()
{
    // Create Queues
    xQueueCreate(TASK_SNACKY_QUEUE_LENGTH, sizeof(uint8_t));

    // Create Task
    BaseType_t ret;
    ret = xTaskCreate(task_snacky, TASK_SNACKY_TASK_NAME, TASK_SNACKY_STACK_SIZE, NULL, TASK_SNACKY_TASK_PRIORITY, &snackyCtrl->task_handle);
    assert(pdPASS == ret);
    
    // If sucessful, delete the task and exit gracefully.
    if (ret == pdPASS)
    {
        vTaskDelete( snackyCtrl->task_handle );
    }
}

void __attribute__((noreturn)) task_snacky (void * pvParameters) 
{
    for(;;)
    {
        ESP_LOGI(TAG, "HI");
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

void task_snacky_deinit(TaskHandle_t task_snacky_handle)
{
    vTaskDelete(snackyCtrl->task_handle);
}
