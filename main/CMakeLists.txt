set(COMPONENT_SRCS "data.c" "mqtt.c" "main.c" "main.c data.c mqtt.c nvs.c wifi.c DFRobot_OxygenSensor.cpp I2C.cpp DTH_Turbidity.cpp OneWire.cpp jsn_sr04t.cpp DallasTemperature.cpp DS18B20.cpp DFRobot_ESP_PH.cpp DFRobot_EC.cpp GPIO.cpp AquaData.cpp")
set(COMPONENT_ADD_INCLUDEDIRS "include")

register_component()