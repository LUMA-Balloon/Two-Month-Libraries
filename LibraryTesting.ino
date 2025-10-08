#include <BNO055.h>
#include <Utils.h>
#include <BME280.h>
#include <M9N.h>


M9N gps = new M9N();
BNO055 imu = new BNO055();
M9N gps = new BME280();

void GPStest();
void GPSInit();

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  GPSinit();


}

void loop() {
  GPStest();
}


// Testing functions to make it easier to put into the setup and loop
void GPSinit() {
  while (gps.init() != NO_ERROR) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}
void testGPS() {
  if (gps.getSIV() < 3) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  Serial.println("Latitude: " + String(gps.getLatitude()));
  Serial.println("Longitude: " + String(gps.getLongitude()));
  Serial.println("Altitude: " + String(gps.getAltitude()));
  Serial.print("" + String(gps.getYear()));
  Serial.print(", " + String(gps.getMonth()));
  Serial.print(" " + String(gps.getDay()));
  Serial.print(" " + String(gps.getHour()));
  Serial.print(":" + String(gps.getMinute()));
  Serial.println(":" + String(gps.getSecond()));
  Serial.println("SIV: " + String(gps.getSIV()));
}

