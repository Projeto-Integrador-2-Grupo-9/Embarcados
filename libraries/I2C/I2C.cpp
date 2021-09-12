#include "I2C.h"
#include <Arduino.h>

DFRobot_OxygenSensor Oxygen;

void oxygen_sensor_init() {
  while(!Oxygen.begin(Oxygen_IICAddress)) {
    delay(1000);
  }
}

void icc_init() {
    oxygen_sensor_init();
}