#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "task_config.h"

#include "task_reader.h"

typedef struct ReaderCtrl_s
{
    TaskHandle_t    task_handle;
} ReaderCtrl_t;

static ReaderCtrl_t * ReaderCtrl = NULL;

void task_reader_init()
{
    // Does task_reader really need a queue? It only sends information outwards? Maybe in the future where we would like to disable it temporarily.
    // Create Queues
    // xQueueCreate(DEFAULT_QUEUE_LENGTH, sizeof(uint8_t));

    // Create Task
    BaseType_t ret = xTaskCreate(task_reader, TASK_READER_NAME, TASK_READER_STACK_SIZE, NULL, 1, &ReaderCtrl->task_handle);
    assert(ret == pdPASS);
}

void task_reader();

void task_reader_deinit()
{
    vTaskDelete(ReaderCtrl->task_handle);
}

