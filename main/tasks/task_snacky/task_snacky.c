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
} SnackyCtrl_t;

// --- Local Variables

static SnackyCtrl_t * snackyCtrl = NULL;

// --- Functions

void task_snacky_init()
{
    // Create control struct to be populated.
    SnackyCtrl_t * ctrl = malloc(sizeof(SnackyCtrl_t)); // Do not cast return from malloc in C?

    // Create Queue
    ctrl->queue_handle = xQueueCreate(TASK_SNACKY_QUEUE_LENGTH, sizeof(SnackyInEvent_e));
    assert(ctrl->queue_handle != NULL); 

    // Create Task
    BaseType_t ret = xTaskCreate(task_snacky, TASK_SNACKY_NAME, TASK_SNACKY_STACK_SIZE, NULL, TASK_SNACKY_TASK_PRIORITY, &ctrl->task_handle);
    assert(pdPASS == ret);

    snackyCtrl = ctrl;
}

void __attribute__((noreturn)) task_snacky (void * pvParameters) 
{
    // Recieve messages from it's queue
    while(true)
    {
        vTaskDelay(5000/portTICK_PERIOD_MS);
        SnackyInEvent_e event = SnackyInEvent_None;
        // xQueueRecive return pdPASS if it sucessfully obtains an item from the queue.
        xQueueReceive(snackyCtrl->queue_handle, &event, portMAX_DELAY);

        // Handle the incoming event.
        if (event != SnackyInEvent_None)
        {
            ESP_LOGI(TAG, "Received event from queue: %d", event);
        } else
        {
            ESP_LOGI(TAG, "No event received.");
        }
    }
}

void task_snacky_deinit(TaskHandle_t task_snacky_handle)
{
    vTaskDelete(snackyCtrl->task_handle);
}
