#ifndef BME280_h
#define BME280_h

#include "Arduino.h"
#include "Utils.h"


class BME280: public Sensor {
private:
    float pressure = std::nullopt;
    float temperature = std::nullopt;
    float humidity = std::nullopt;
    float altitude = std::nullopt;
public:
    Error init();
    bool prefetchData();
    float getPressure();
    float getTemperature();
    float getAltitude();
    float getHumidity();
};


#endif