#ifndef __GPIO_H__
#define __GPIO_H__

#include <DS18B20.h>
#include "DTH_Turbidity.h"
#include "DFRobot_ESP_PH.h"
#include "EEPROM.h"
#include "DFRobot_EC.h"
#include "jsn_sr04t.h"

DTH_Turbidity turbSensor;
DS18B20 temperatureSensor;
DFRobot_ESP_PH ph;
DFRobot_EC ec;

void gpio_init_2();

#endif /* GPIO_H */