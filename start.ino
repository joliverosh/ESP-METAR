#include <ESP8266WebServer.h>
#include <WiFiManager.h> // --> https://github.com/tzapu/WiFiManager
#include <ESP8266mDNS.h>

#define HOSTNAME "METAR-"


//#########################################################################################
int AutoConnect(){
  FlashMatrix();
  int connAttempts = 0; 
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings
    //wifiManager.resetSettings();


  String hostname(HOSTNAME);
  hostname += String(ESP.getChipId(), HEX);
  if (!wifiManager.autoConnect((const char *)hostname.c_str())) {
    delay(3000);
    WiFi.disconnect(true);
    ESP.reset();
    delay(5000);
  }
}

//#########################################################################################
void StartNTP(char* Timezone){
  //CHANGE THE POOL WITH YOUR CITY. SEARCH AT https://www.ntppool.org/zone/@
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");    
  setenv("TZ", Timezone,0);
}
