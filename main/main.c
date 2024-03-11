#include <stdio.h>
<<<<<<< Updated upstream

void app_main(void)
{
    
}
=======
#include "freertos/FreeRTOS.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_adc/adc_cali_scheme.h"

static const char* TAG = "main";
static adc_cali_line_fitting_efuse_val_t EFUSE_TP = ADC_CALI_LINE_FITTING_EFUSE_VAL_EFUSE_TP;
static adc_cali_line_fitting_efuse_val_t EFUSE_VREF = ADC_CALI_LINE_FITTING_EFUSE_VAL_EFUSE_VREF;


void app_main(void)
{
    // Setup adc_cali_line_fitting_config_t
    //  ::unit_id: adc raw results input.
    //  ::attn: attenuation.
    //  ::bitwidth: bit width of adc raw result.
    //  char * efuse_adc_scheme = 'none'

    if (ESP_OK == adc_cali_scheme_line_fitting_check_efuse(&EFUSE_TP)) {
        ESP_LOGW(TAG, "EFUSE_TP supported");
    } else {
        ESP_LOGW(TAG, "EFUSE_TP not supported");
    }
    //Check Vref is burned into eFuse
    if (ESP_OK == adc_cali_scheme_line_fitting_check_efuse(&EFUSE_VREF)) {
        ESP_LOGW(TAG, "EFUSE_VREF supported");
    } else {
        ESP_LOGW(TAG, "EFUSE_VREF not supported");
    }
}
>>>>>>> Stashed changes
