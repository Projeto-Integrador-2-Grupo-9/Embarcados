#include "GPIO.h"
#include <DS18B20.h>
#include "DTH_Turbidity.h"
#include "DFRobot_ESP_PH.h"
#include "EEPROM.h"
#include "DFRobot_EC.h"
#include "jsn_sr04t.h"

DTH_Turbidity turbiditySensor;
DS18B20 temperatureSensor;
DFRobot_ESP_PH phSensor;
DFRobot_EC ecSensor;

void ec_sensor_init()
{
    ecSensor.begin();
}

void ph_sensor_init()
{
    EEPROM.begin(32); //needed to permit storage of calibration value in eeprom
    phSensor.begin();
}

void turbidity_sensor_init()
{
    turbiditySensor.begin(TURBIDITY_SENSOR_PIN, -1);
}

void temperature_sensor_init()
{
    temperatureSensor.begin(TEMPERATURE_SENSOR);
}

void init_gpio()
{
    temperature_sensor_init();
    turbidity_sensor_init();
    ph_sensor_init();
    ec_sensor_init();
    init_ultrasound_sensors();
}
