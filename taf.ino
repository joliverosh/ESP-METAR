//https://tgftp.nws.noaa.gov/data/forecasts/taf/stations/SKCL.TXT

#include <WiFiClientSecureBearSSL.h>
#include <ESP8266HTTPClient.h>

//----------------------------------------------------------------------------------------------------
void GET_TAF(String station) { //client function to send/receive GET request data.
  
  const char* server      = "tgftp.nws.noaa.gov";
  const uint8_t fingerprint[20] = {0x45, 0xBE, 0x50, 0xDA, 0x9C, 0xE3, 0x86, 0x73, 0xE1, 0xB3, 0x74, 0x77, 0x95, 0x36, 0x8B, 0xE5, 0x94, 0x86, 0x2F, 0xB6};

  String metar         = " ";
  bool metar_status    = false;
  const int time_delay = 20000; 
  
  String url = "/data/forecasts/taf/stations/"+station+".TXT";

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setFingerprint(fingerprint);
  HTTPClient https;
  if (https.begin(*client, "https://tgftp.nws.noaa.gov"+url)) {  // HTTPS
     int httpCode = https.GET();
     if (httpCode > 0) {
     if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
         String taf = https.getString();
         Serial.println(taf);
         display_message(taf);   
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
    while (xim < 10000){
      DispClock();  
      xim++;
   }
}