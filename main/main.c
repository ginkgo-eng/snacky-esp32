#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_err.h"

#include "task_snacky.h"

void app_main(void)
{
    task_snacky_init();
}