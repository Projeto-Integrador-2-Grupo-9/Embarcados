#include <stdio.h>
#include "AquaData.h"

extern "C" void app_main()
{
    AquaData aquaData;
    aquaData.init_sensors();
    aquaData.calibrate_sensors();
    aquaData.load_data();
    printf("Olá mundo!");
    fflush(stdout);
}