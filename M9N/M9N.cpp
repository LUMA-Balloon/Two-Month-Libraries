#include <Arduino.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <data.h>
#include <optional>
#include "utilities/time.h"
#include "board-io/sensors.h"
#include "havoc.h"

 Position mostRecentPos;
 UTCTime mostRecentTime;
 int mostRecentSIV;

 void pvtCallback(UBX_NAV_PVT_data_t *ubxDataStruct) {
    mostRecentPos = {
        ((double)ubxDataStruct->lat) * pow(10, -7),
        ((double)ubxDataStruct->lon) * pow(10, -7),
        ubxDataStruct->height / 1000.0
    };   
    mostRecentTime = {
        (int)ubxDataStruct->year,
        (int)ubxDataStruct->month,
        (int)ubxDataStruct->day,
        (int)ubxDataStruct->hour,
        (int)ubxDataStruct->min,
        (int)ubxDataStruct->sec,
    };
    mostRecentSIV = ubxDataStruct->numSV;
}

void M9N::init() {
    while (!m9n.begin()) {
        // TODO ERROR
    }
    m9n.setI2COutput(COM_TYPE_UBX);
    m9n.setNavigationFrequency(5);
    if (!m9n.setDynamicModel(DYN_MODEL_AIRBORNE4g)) {
        // TODO ERROR
    }
    m9n.saveConfiguration();
    m9n.setAutoPVTcallbackPtr(&pvtCallback);

    bool sivCheck = config.waitForGPSLock;
    while (sivCheck) {
        m9n.checkUblox();
        m9n.checkCallbacks();
        switch (mostRecentSIV) {
            // TODO ERRORS
            default:
                sivCheck = false;
                break;
        }
    }
}

bool M9N::prefetchData() {
    m9n.checkUblox();
    m9n.checkCallbacks();
    pos = mostRecentPos;
    time = mostRecentTime;
    SIV = mostRecentSIV;
    return true;
}

std::optional<Position> M9N::getPosition() {
    return pos;
}

std::optional<UTCTime> M9N::getUTCTime() {
    return time;
}

std::optional<int> M9N::getSIV() {
    return SIV;
}
