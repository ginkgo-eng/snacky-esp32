#include "esp_wifi.h"

#include "task_wifi.h"

static const char *TAG = "task_wifi";

void task_wifi_init(void)
{
    esp_wifi_init();
}