#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_adc/adc_continuous.h"

#define SAMPLE_FREQUENCY_HZ (20 * 1000)
#define ADC_PATTERN_NUM 1
#define ADC_CONVERSION_MODE ADC_CONV_SINGLE_UNIT_1
#define ADC_OUTPUT_FORMAT  ADC_DIGI_OUTPUT_FORMAT_TYPE1

#define ADC_ATTEN ADC_ATTEN_DB_0 
#define ADC_GPIO 36
#define ADC_BIT_WIDTH SOC_ADC_DIGI_MAX_BITWIDTH



static const char* TAG = "main";

static adc_cali_line_fitting_efuse_val_t EFUSE_TP = ADC_CALI_LINE_FITTING_EFUSE_VAL_EFUSE_TP;
static adc_cali_line_fitting_efuse_val_t EFUSE_VREF = ADC_CALI_LINE_FITTING_EFUSE_VAL_EFUSE_VREF;
static adc_cali_scheme_ver_t ADC_LINE_FITTING = ADC_CALI_SCHEME_VER_LINE_FITTING;
static adc_cali_scheme_ver_t ADC_CURVE_FITTING = ADC_CALI_SCHEME_VER_CURVE_FITTING;

static void continuous_adc_init(int gpio, adc_continuous_handle_t *out_handle){

    // Obtain ADC unit and channel for target GPIO.
    adc_unit_t gpio_adc_unit = (adc_unit_t) malloc(sizeof(adc_unit_t));
    adc_channel_t gpio_adc_channel = (adc_channel_t) malloc(sizeof(adc_channel_t));
    if (ESP_OK != adc_continuous_io_to_channel(gpio, &gpio_adc_unit, &gpio_adc_channel)){
        ESP_LOGE(TAG, "Invalid GPIO for ADC.");
        return;
    }

    // Checks passed, continue with initialization.
    adc_continuous_handle_t handle = NULL;

    // Configure continuous mode ADC handle.
    adc_continuous_handle_cfg_t adc_handle_config = {
        .max_store_buf_size = 1024,
        .conv_frame_size = 100,
    };

    // Create ADC handle.
    adc_continuous_handle_t adc_handle = malloc(sizeof(adc_continuous_handle_t));
    ESP_ERROR_CHECK(adc_continuous_new_handle(&adc_handle_config, &adc_handle));

    // Configure continuous mode ADC.
    adc_continuous_config_t adc_config = {
        .pattern_num = ADC_PATTERN_NUM,
        // .adc_pattern = ; to be defined later and added to config.
        .sample_freq_hz = SAMPLE_FREQUENCY_HZ,
        .conv_mode = ADC_CONVERSION_MODE,
        .format = ADC_OUTPUT_FORMAT,
    };

    adc_digi_pattern_config_t adc_pattern = {
        .atten = ADC_ATTEN,
        .channel = gpio_adc_channel,
        .unit = gpio_adc_unit,
        .bit_width= ADC_BIT_WIDTH,
    };

    adc_config.adc_pattern = &adc_pattern;
    ESP_ERROR_CHECK(adc_continuous_config(handle, &adc_config));

    *out_handle = handle;
}

void app_main(void)
{
    // Configure logging library verbosity.
    (void) esp_log_level_set(TAG, ESP_LOG_VERBOSE);

    // Setup adc_cali_line_fitting_config_t
    //  ::unit_id: adc raw results input.
    //  ::attn: attenuation.
    //  ::bitwidth: bit width of adc raw result.
    //  char * efuse_adc_scheme = 'none'

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

    adc_continuous_handle_t pot_adc_handle = (adc_continuous_handle_t) malloc(sizeof(adc_continuous_handle_t));
    //continuous_adc_init(27, &pot_adc_handle);
    //ESP_ERROR_CHECK(adc_continuous_deinit(pot_adc_handle));
}