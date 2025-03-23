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
    QueueHandle_t   queue_handle;
    uint8_t         event;
    
    
} SnackyCtrl_t;

// --- Local Variables

static SnackyCtrl_t * snackyCtrl = NULL;

// --- Functions

void task_snacky_init()
{
    // Create Queue
    QueueHandle_t queue_handle = xQueueCreate(TASK_SNACKY_QUEUE_LENGTH, sizeof(uint8_t));
    assert(queue_handle != NULL);
    snackyCtrl->queue_handle = queue_handle;

    // Create Task
    BaseType_t ret = xTaskCreate(task_snacky, TASK_SNACKY_NAME, TASK_SNACKY_STACK_SIZE, NULL, TASK_SNACKY_TASK_PRIORITY, &snackyCtrl->task_handle);
    assert(pdPASS == ret);
}

void __attribute__((noreturn)) task_snacky (void * pvParameters) 
{
    // Recieve messages from it's queue
    while(true)
    {
        snackyCtrl->event = SnackyInEvent_None;
        // xQueueRecive return pdPASS if it sucessfully obtains an item from the queue.
        xQueueReceive(snackyCtrl->queue_handle, &snackyCtrl->event, portMAX_DELAY);

        // Handle the incoming event.
        if (snackyCtrl->event != SnackyInEvent_None)
        {
            ESP_LOGI(TAG, "Received event from queue: %d", snackyCtrl->event);
        }
    }
}

void task_snacky_deinit(TaskHandle_t task_snacky_handle)
{
    vTaskDelete(snackyCtrl->task_handle);
}
