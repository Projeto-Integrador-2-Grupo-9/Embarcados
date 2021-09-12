#include "I2C.h"
#include <Arduino.h>

DFRobot_OxygenSensor Oxygen;

void oxygen_sensor_init() {
  while(!Oxygen.begin(Oxygen_IICAddress)) {
    delay(1000);
  }
}

void init_i2c() {
    oxygen_sensor_init();
}