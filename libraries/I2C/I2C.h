#ifndef __I2C_H__
#define __I2C_H__

#include <DFRobot_OxygenSensor.h>

/* OxygenSensor */

#define COLLECT_NUMBER    10             // collect number, the collection range is 1-100.
#define Oxygen_IICAddress ADDRESS_3


void icc_init();

#endif /* I2C_H */