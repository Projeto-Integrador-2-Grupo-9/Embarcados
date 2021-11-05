#ifndef DATA_H
#define DATA_H

/****************************************************************************/
/*!                            Structs                                      */
typedef struct DeviceData
{
    float temperature;
    float conductivity;
    float ph;
    float oxygen;
    float turbidity;
    float lat;
    float lng;
} DeviceData;

/****************************************************************************/
/*!                         Functions                                       */

/*!
 * @brief This function parse JSON.
 */
void parser(char * buffer);

#endif /* DATA_H_ */

