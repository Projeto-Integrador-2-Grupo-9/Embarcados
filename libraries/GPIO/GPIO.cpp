#include "GPIO.h"
#include <DS18B20.h>
#include "DTH_Turbidity.h"
#include "DFRobot_ESP_PH.h"
#include "EEPROM.h"
#include "DFRobot_EC.h"
#include "jsn_sr04t.h"

#define TURBIDITY_SENSOR_PIN A0
#define TEMPERATURE_SENSOR 15

DTH_Turbidity turbSensor(TURBIDITY_SENSOR_PIN);
DS18B20 temperature;
DFRobot_ESP_PH ph;
DFRobot_EC ec;

void ec_sensor_init()
{
    ec.begin();
}

void ph_sensor_init()
{
    EEPROM.begin(32); //needed to permit storage of calibration value in eeprom
    ph.begin();
}

void turbidity_sensor_init()
{
    turbSensor.begin(TURBIDITY_SENSOR_PIN, -1);
}

void temperature_sensor_init()
{
    temperature.begin(TEMPERATURE_SENSOR);
}

void gpio_init_2()
{
    temperature_sensor_init();
    turbidity_sensor_init();
    ph_sensor_init();
    init_ultrasound_sensors();
}
