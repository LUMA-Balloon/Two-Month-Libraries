#include "Arduino.h"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include "Utils.h"
#include "SHC_M9N.h"

int mostRecentYear = 0;
int mostRecentMonth = 0;
int mostRecentDay = 0;
int mostRecentHour = 0;
int mostRecentMinute = 0;
int mostRecentSecond = 0;
int mostRecentSIV = 0;
double mostRecentLongitude = 0.0;
double mostRecentLatitude = 0.0;
double mostRecentAltitude = 0.0;


// void pvtCallback(UBX_NAV_PVT_data_t *ubxDataStruct) {
//     mostRecentPos = {
//         ((double)ubxDataStruct->lat) * pow(10, -7),
//         ((double)ubxDataStruct->lon) * pow(10, -7),
//         ubxDataStruct->height / 1000.0
//     };   
//     mostRecentTime = {
//         (int)ubxDataStruct->year,
//         (int)ubxDataStruct->month,
//         (int)ubxDataStruct->day,
//         (int)ubxDataStruct->hour,
//         (int)ubxDataStruct->min,
//         (int)ubxDataStruct->sec,
//     };
//     mostRecentSIV = ubxDataStruct->numSV;
// }
void pvtCallback(UBX_NAV_PVT_data_t *ubxDataStruct) {
    mostRecentLatitude = ((double)ubxDataStruct->lat) * pow(10, -7);
    mostRecentLongitude = ((double)ubxDataStruct->lon) * pow(10, -7);
    mostRecentAltitude = ubxDataStruct->height / 1000.0;
      
    mostRecentYear = (int)ubxDataStruct->year;
    mostRecentMonth = (int)ubxDataStruct->month;
    mostRecentDay = (int)ubxDataStruct->day;
    mostRecentHour = (int)ubxDataStruct->hour;
    mostRecentMinute = (int)ubxDataStruct->min;
    mostRecentSecond = (int)ubxDataStruct->sec;
    mostRecentSIV = ubxDataStruct->numSV;
}

Error M9N::init() {
    if (!m9n.begin()) {
        return M9N_ERROR;
    }
    m9n.setI2COutput(COM_TYPE_UBX);
    m9n.setNavigationFrequency(5);
    if (!m9n.setDynamicModel(DYN_MODEL_AIRBORNE4g)) {
        return M9N_ERROR;
    }
    m9n.saveConfiguration();
    m9n.setAutoPVTcallbackPtr(&pvtCallback);

    // bool sivCheck = config.waitForGPSLock;

    // Make it not block
    // while (sivCheck) {
    //     m9n.checkUblox();
    //     m9n.checkCallbacks();
    //     switch (mostRecentSIV) {
    //         // TODO ERRORS
    //         default:
    //             sivCheck = false;
    //             break;
    //     }
    // }
    return NO_ERROR;
}

bool M9N::prefetchData() {
    m9n.checkUblox();
    m9n.checkCallbacks();
    longitude = mostRecentLongitude;
    latitude = mostRecentLatitude;
    altitude = mostRecentAltitude;
    year = mostRecentYear;
    month = mostRecentMonth;
    day = mostRecentDay;
    hour = mostRecentHour;
    minute = mostRecentMinute;
    second = mostRecentSecond;
    SIV = mostRecentSIV;
    return true;
}

double M9N::getLatitude() {
    return latitude;
}
double M9N::getLongitude() {
    return longitude;
}
double M9N::getAltitude(){
    return altitude;
}

int M9N::getYear() {
    return year;
}
int M9N::getMonth() {
    return month;
}
int M9N::getDay() {
    return day;
}
int M9N::getHour() {
    return hour;
}
int M9N::getMinute() {
    return minute;
}
int M9N::getSecond() {
    return second;
}

int M9N::getSIV() {
    return SIV;
}