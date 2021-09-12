#include "DS18B20.h"

DS18B20::DS18B20()
{
}

DS18B20::~DS18B20()
{
}

void DS18B20::begin(uint32_t bus)
{
    OneWire oneWire(bus);
    DallasTemperature sensors(&oneWire);

    this->sensors = sensors;

    sensors.begin();

    this->hasDevice = sensors.getDeviceCount();
    if (this->hasDevice)
    {
        // Search the wire for address
        if (sensors.getAddress(this->deviceAddress, this->hasDevice))
        {
            // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
            sensors.setResolution(this->deviceAddress, TEMPERATURE_PRECISION);
        }
    }
}

float DS18B20::get_temperature()
{
    if (this->hasDevice)
    {
        // Search the wire for address
        if (sensors.getAddress(this->deviceAddress, this->hasDevice))
        {
            return sensors.getTempC(this->deviceAddress);
        }
    }
    return TEMPERATURE_ERROR;
}