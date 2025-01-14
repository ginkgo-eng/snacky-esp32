#include "esp_adc/adc_cali_scheme.h"
#include "esp_adc/adc_continuous.h"

static const char* TAG = "adc";

static adc_cali_line_fitting_efuse_val_t EFUSE_TP = ADC_CALI_LINE_FITTING_EFUSE_VAL_EFUSE_TP;
static adc_cali_line_fitting_efuse_val_t EFUSE_VREF = ADC_CALI_LINE_FITTING_EFUSE_VAL_EFUSE_VREF;
static adc_cali_scheme_ver_t ADC_LINE_FITTING = ADC_CALI_SCHEME_VER_LINE_FITTING;
static adc_cali_scheme_ver_t ADC_CURVE_FITTING = ADC_CALI_SCHEME_VER_CURVE_FITTING;

// Check e-fuse for adc line fitting calibration schemes.
if (ESP_OK == adc_cali_scheme_line_fitting_check_efuse(&EFUSE_TP)) {
    ESP_LOGI(TAG, "EFUSE_TP supported");
} else {
    ESP_LOGI(TAG, "EFUSE_TP not supported");
}
if (ESP_OK == adc_cali_scheme_line_fitting_check_efuse(&EFUSE_VREF)) {
    ESP_LOGI(TAG, "EFUSE_VREF supported");
} else {
    ESP_LOGI(TAG, "EFUSE_VREF not supported");
}

// Check avaliable adc schemes.
if (ESP_OK == adc_cali_check_scheme(&ADC_LINE_FITTING)){
    ESP_LOGI(TAG, "ADC line fitting is supported");
} else {
    ESP_LOGI(TAG, "ADC line fitting is not supported");
}
if (ESP_OK == adc_cali_check_scheme(&ADC_CURVE_FITTING)){
    ESP_LOGI(TAG, "ADC curve fitting is supported");
} else {
    ESP_LOGI(TAG, "ADC curve fitting is not supported");
}
