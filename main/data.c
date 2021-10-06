/****************************************************************************/
/*                       Header includes                                    */

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "cJSON.h"

#include "nvs.h"
#include "mqtt.h"

/****************************************************************************/
/*! @file data.c
 * @brief Data structure to save the data
 */
#include "data.h"

/****************************************************************************/
/*!                        Global Statements                                */

extern int id;
extern char room[50];
extern DeviceData device_data;
extern xSemaphoreHandle mqttSemaphore;

/****************************************************************************/
/*!                         Functions                                       */


/*!
 * @brief This function parse JSON.
 */
void parser(char * buffer)
{
    cJSON * json = cJSON_Parse (buffer);
    if(id < 0 )
    {
        cJSON * id_json  = cJSON_GetObjectItemCaseSensitive(json, "id");
        if (id_json)
        {
            id = id_json->valueint;
            nvs_set_data();
            xSemaphoreGive(mqttSemaphore);
        }
    } 
    else
    {
        cJSON * status_json  = cJSON_GetObjectItemCaseSensitive(json, "status");
        if (status_json)
        {
            int status = status_json->valueint;
            if (status != device_data.device_status)
            {
                // set_device_status(status);
            }
        }
    }
    cJSON_Delete(json);
}
