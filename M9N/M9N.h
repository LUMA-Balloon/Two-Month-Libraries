#ifndef M9N_h
#define M9N_h

#include "Arduino.h"

class M9N : public Sensor {
private:
    SFE_UBLOX_GNSS m9n;
    double longitude = 0.0;
    double latitude = 0.0;
    double altitude = 0.0;
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    int SIV = 0;
public:
    void init();
    bool prefetchData();
    double getLatitude();
    double getLongitude();
    double getAltitude();
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMinute();
    int getSecond();
    int getSIV();
};


#endif