#include "AquaData.h"
#include "GPIO.h"
#include "I2C.h"
#include "DS18B20.h"
#include "DTH_Turbidity.h"
#include "DFRobot_ESP_PH.h"
#include "DFRobot_EC.h"
#include "jsn_sr04t.h"
#include "Arduino.h"

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
    float voltagePH = analogRead(PH_PIN)/1024.0*5000;
    float voltageEC = analogRead(EC_PIN)/1024.0*5000;
    float temperature = temperatureSensor.get_temperature();

    ecSensor.calibration(voltageEC, temperature);
    phSensor.calibration(voltagePH, temperature);
    calibrate_all_sensors();
}

void AquaData::load_data()
{
    float voltagePH = analogRead(PH_PIN)/1024.0*5000;
    float voltageEC = analogRead(EC_PIN)/1024.0*5000;

    this->temperature = temperatureSensor.get_temperature();
    this->conductivity = ecSensor.readEC(voltageEC, this->temperature);
    this->ph = phSensor.readPH(voltagePH, this->temperature);
    this->oxygen = oxygenSensor.ReadOxygenData(Oxygen_IICAddress);
    this->turbidity = turbiditySensor.readTurbidity();
    for (int i = 1; i <= NUM_SENSORS; i++)
        this->proximity[i] = get_distance(i);
}