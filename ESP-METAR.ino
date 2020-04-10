#include <ESP8266WiFi.h>

char* TimeZ = "COT+5"; // Time zone "COT+5" http://famschmid.net/timezones.html

void setup() {
  Serial.begin(115200);
  StartMatrix(1); // rotationOfDisplays
  AutoConnect();
  StartNTP(TimeZ);
}

void loop() {
  GET_METARD("SKCL"); // Airport meteorological station decoded METAR
  GET_TAF("SKCL");    // Airport meteorological station TAF
  GET_METAR("SKPE");  // Airport meteorological station METAR
//  GET_METAR("SKAR");
//  GET_METAR("SKPP");
//  GET_METAR("SKRG");
//  GET_METAR("SKMD");
}
