/****************************************************************************/
/*                       Header includes                                    */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

#include "cJSON.h"

#include "wifi.h"
#include "data.h"
#include "mqtt.h"

/****************************************************************************/
/*!                              Macros                                     */

#define TAG "MQTT"

/****************************************************************************/
/*!                         global statement                                */

extern int id;
extern DeviceData device_data;
extern xSemaphoreHandle mqttSemaphore;

char mac[18] = {0};

esp_mqtt_client_handle_t client;
esp_mqtt_client_config_t mqtt_config = {
    .uri = "mqtt://test.mosquitto.org",
};

/****************************************************************************/
/*!                         Functions                                       */

/*!
 *  @brief Task Function used to update sersor data
 */
void sendSensorData(void *params)
{
    char message[300];
    char topic[100];
    while (true)
    {
        sprintf(topic, "AD/sensor_data");
        sprintf(message, "{\"device\":\"%s\", \"temperature\":%f, \"conductivity\":%f, \"ph\":%f, \"dissolved_oxygen\":%f, \"turbidity\":%f, \"timestamp\": \"2021-11-04 17:44:48\"}", mac, device_data.temperature, device_data.conductivity, device_data.ph, device_data.oxygen, device_data.turbidity);
        mqtt_send_message(topic, message);
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

/*!
 *  @brief Function used to update device positon
 */
void sendPosition(void *params)
{
    char message[200];
    char topic[100];
    while (true)
    {
        sprintf(topic, "AD/position_data");
        sprintf(message, "{\"device\":\"%s\", \"current_position\":{\"lat\":%f, \"lng\":%f}, \"timestamp\": \"2021-11-04 17:44:48\"}", mac, device_data.lat, device_data.lng);
        mqtt_send_message(topic, message);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

/*!
 *  @brief Function used to subscribe
 */
void mqtt_subscribe()
{
    char topic[50];
    char message[200];
    setMacAddress(mac);
    sprintf(message, "{\"new_device\":\"%s\", \"starting_position\":{\"lat\":%f, \"lng\":%f}}", mac, device_data.lat, device_data.lng);
    mqtt_send_message("AD/devices", message);
    sprintf(topic, "AD/devices/%s", mac);
    esp_mqtt_client_subscribe(client, topic, 2);
}

/*!
 *  @brief Function used to reveive message
 */
void mqtt_receive_message(esp_mqtt_event_handle_t event)
{
    printf("%.*s\r\n", event->data_len, event->data);
    // parser(event->data);
}

/*!
 *  @brief Function used to send message
 */
void mqtt_send_message(char *topic, char *message)
{
    esp_mqtt_client_publish(client, topic, message, 0, 2, 0);
    printf("%s:%s\n", topic, message);
}

/*!
 *  @brief Function used to process mqtt event
 */
static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    client = event->client;

    switch (event->event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        mqtt_subscribe();
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        mqtt_receive_message(event);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
    return ESP_OK;
}

/*!
 *  @brief Function used to mqtt event handler
 */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    mqtt_event_handler_cb(event_data);
}

/**
  * @brief Function to init mqtt.
  */
void mqtt_start()
{
    client = esp_mqtt_client_init(&mqtt_config);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
}
