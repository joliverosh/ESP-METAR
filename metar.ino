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

#include <WiFiClientSecureBearSSL.h>
#include <ESP8266HTTPClient.h>

//----------------------------------------------------------------------------------------------------
void GET_METAR(String station, int inform) { //client function to send/receive GET request data.
  if (station == "") {return;}
  
  const char* server      = "tgftp.nws.noaa.gov";
  const uint8_t fingerprint[20] = {0x45, 0xBE, 0x50, 0xDA, 0x9C, 0xE3, 0x86, 0x73, 0xE1, 0xB3, 0x74, 0x77, 0x95, 0x36, 0x8B, 0xE5, 0x94, 0x86, 0x2F, 0xB6};

  String metar         = " ";
  String url= "";
  String metarurl="/data/observations/metar/stations/";
  String tafurl="/data/forecasts/taf/stations/";
  String decodedurl="/data/observations/metar/decoded/";

  if (inform == 1){
  url = metarurl+station+".TXT";
  }
  if (inform == 2){
  url = tafurl+station+".TXT";
  }
  if (inform == 3){
  url = decodedurl+station+".TXT";
  }

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setFingerprint(fingerprint);
  HTTPClient https;
  if (https.begin(*client, "https://tgftp.nws.noaa.gov"+url)) {  // HTTPS
     int httpCode = https.GET();
     if (httpCode > 0) {
     if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
         String metar = https.getString();
         Serial.println(metar);
         display_message(metar);   
         }
      } 
      else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
          } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
    int xim = 0;
    while (xim < time_delay){
      DispClock();  
      xim++;
    }
}
