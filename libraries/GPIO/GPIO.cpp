#include "GPIO.h"

#define TURBIDITY_SENSOR_PIN A0
#define TEMPERATURE_SENSOR 15

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
    temperatureSensor.begin(TEMPERATURE_SENSOR);
}

void init_gpio()
{
    temperature_sensor_init();
    turbidity_sensor_init();
    ph_sensor_init();
    init_ultrasound_sensors();
}
