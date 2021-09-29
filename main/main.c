/****************************************************************************/
/*                       Header includes                                    */

#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_sleep.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp32/rom/uart.h"
#include "freertos/semphr.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/rtc_io.h"
#include "mqtt_client.h"

#include "nvs.h"
#include "wifi.h"

/****************************************************************************/
/*!                              Macros                                     */

// #define SECOND 1000000

/****************************************************************************/
/*!                        Global Statements                                */

xSemaphoreHandle wifiSemaphore = NULL;
// xSemaphoreHandle mqttSemaphore = NULL;

// AquaData aquaData;

// extern esp_mqtt_client_handle_t client; 

/****************************************************************************/
/*!                         Functions                                       */

/**
  * @brief function main.
  */
void app_main(void)
{
    nvs_init();

    // aquaData.init_sensors();
    // aquaData.calibrate_sensors();
    // aquaData.load_data();

    wifiSemaphore = xSemaphoreCreateBinary();
    // mqttSemaphore = xSemaphoreCreateBinary();

    wifi_init();

    // esp_sleep_enable_timer_wakeup(30 * SECOND);

    // xTaskCreate(&sendSensorData, "Send Sensor Data", 4096, NULL, 1, NULL);

    // if (xSemaphoreTake(wifiSemaphore, portMAX_DELAY))
    // {
    //     mqtt_start();
    // }
}