#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "OneWire.h"
#include "DallasTemperature.h"
#include <cstdint>

#define TEMPERATURE_PRECISION 12
#define TEMPERATURE_ERROR -1.f

class DS18B20{  
public:
  DS18B20();
  ~DS18B20();
  void begin(uint32_t bus);
  float get_temperature();

private:
    DallasTemperature sensors;
    int hasDevice;
    DeviceAddress deviceAddress;
};

#endif /* DS18B20_H */