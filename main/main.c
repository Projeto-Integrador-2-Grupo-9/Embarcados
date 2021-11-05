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
#include "mqtt.h"
#include "data.h"

/****************************************************************************/
/*!                              Macros                                     */

#define SECOND 1000000

/****************************************************************************/
/*!                        Global Statements                                */

xSemaphoreHandle wifiSemaphore = NULL;
xSemaphoreHandle mqttSemaphore = NULL;

DeviceData device_data = {0};

int id = -1;

extern esp_mqtt_client_handle_t client;

/****************************************************************************/
/*!                         Functions                                       */

/**
  * @brief function main.
  */
void app_main(void)
{
  device_data.temperature = 0.f;
  device_data.conductivity = 0.f;
  device_data.ph = 0.f;
  device_data.oxygen = 0.f;
  device_data.turbidity = 0.f;
  device_data.lat = -15.8310f;
  device_data.lng = -47.8460f;

  nvs_init();
  nvs_get_data();

  wifiSemaphore = xSemaphoreCreateBinary();
  mqttSemaphore = xSemaphoreCreateBinary();

  wifi_init();

  esp_sleep_enable_timer_wakeup(30 * SECOND);

  xTaskCreate(&sendSensorData, "Send Sensor Data", 4096, NULL, 1, NULL);

  xTaskCreate(&sendPosition, "Send Position", 4096, NULL, 1, NULL);

  if (xSemaphoreTake(wifiSemaphore, portMAX_DELAY))
  {
    mqtt_start();
  }
}