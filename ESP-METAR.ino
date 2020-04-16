/*
MIT License

Copyright (c) 2020 Jose Luis Oliveros

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <ESP8266WiFi.h>

char* TimeZ = "COT+5"; // Time zone "COT+5" http://famschmid.net/timezones.html

// Airport meteorological station decoded METAR and TAF
String mainStation = "SKCL";

// Airport meteorological station METAR
String stations[5] = {"SKPE", "SKAR", "SKPP", "SKRG", "SKMD"};

void setup() {
  Serial.begin(115200);
  StartMatrix(1); // rotationOfDisplays
  AutoConnect();
  StartNTP(TimeZ);
}

void loop() {
  GET_METAR(mainStation,3); // Airport meteorological station decoded METAR
  GET_METAR(mainStation,2);    // Airport meteorological station TAF
    for (byte i = 0; i < 5; i = i + 1) {
      GET_METAR(stations[i],1);
    }
  
}
