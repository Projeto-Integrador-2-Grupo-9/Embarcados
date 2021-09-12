#include "AquaData.h"
#include "GPIO.h"
#include "I2C.h"
#include "DS18B20.h"
#include "DTH_Turbidity.h"
#include "DFRobot_ESP_PH.h"
#include "DFRobot_EC.h"
#include "jsn_sr04t.h"

#define NUM_SENSORS 4

extern DS18B20 temperatureSensor;
extern DTH_Turbidity turbiditySensor;
extern DFRobot_ESP_PH phSensor;
extern DFRobot_EC ecSensor;
extern DFRobot_OxygenSensor oxygenSensor;

AquaData::AquaData()
{
}

AquaData::~AquaData()
{
}

void AquaData::init_sensors()
{
    init_gpio();
    init_i2c();
}

void AquaData::calibrate_sensors()
{
    float temperature = temperatureSensor.get_temperature();
    ecSensor.calibration(this->voltage, temperature);
    phSensor.calibration(this->voltage, temperature);
    calibrate_all_sensors();
}

void AquaData::load_data()
{
    this->temperature = temperatureSensor.get_temperature();
    this->conductivity = ecSensor.readEC(this->voltage, this->temperature);
    this->ph = phSensor.readPH(this->voltage, this->temperature);
    this->oxygen = oxygenSensor.ReadOxygenData(Oxygen_IICAddress);
    this->turbidity = turbiditySensor.readTurbidity();
    for (uint8_t i = 1; i <= NUM_SENSORS; i++)
        this->proximity[i] = get_distance(i);
}