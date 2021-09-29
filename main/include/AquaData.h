#ifndef __AQUA_DATA_H__
#define __AQUA_DATA_H__

class AquaData
{
public:
    AquaData();
    ~AquaData();
    void init_sensors();
    void calibrate_sensors();
    void load_data();

private:
    float temperature = 0.f;
    float conductivity = 0.f;
    float ph = 0.f;
    float oxygen = 0.f;
    float turbidity = 0.f;
    float proximity[4];
};

#endif /* AQUA_DATA_H */