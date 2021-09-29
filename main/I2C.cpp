#include "I2C.h"
#include <Arduino.h>

DFRobot_OxygenSensor oxygenSensor;

void oxygen_sensor_init() {
  while(!oxygenSensor.begin(Oxygen_IICAddress)) {
    delay(1000);
  }
}

void init_i2c() {
    oxygen_sensor_init();
}