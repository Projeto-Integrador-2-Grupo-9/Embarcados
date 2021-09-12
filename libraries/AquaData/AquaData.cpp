#include "AquaData.h"
#include "GPIO.h"
#include "I2C.h"

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

void AquaData::load_data()
{
    this->temperature = temperatureSensor.get_temperature();
}