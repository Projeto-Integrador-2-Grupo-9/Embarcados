
#include "AquaData.h"

void setup()
{
}

void loop()
{
    AquaData aquaData;
    aquaData.init_sensors();
    aquaData.calibrate_sensors();
    aquaData.load_data();
}