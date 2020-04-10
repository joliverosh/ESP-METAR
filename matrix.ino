#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <time.h>

int MatrixIntensity = 0; // Brightness of the display. (0..15)

// LED Matrix Pin -> ESP8266 Pin
// Vcc            -> 3v  (3V on NodeMCU 3V3 on WEMOS)
// Gnd            -> Gnd (G on NodeMCU)
// DIN            -> D7  (Same Pin for WEMOS)
// CS             -> D6  (Same Pin for WEMOS)
// CLK            -> D5  (Same Pin for WEMOS)

  /*
   * Define if and how the displays are rotated. The first display
   * (0) is the one closest to the Arduino. rotation can be:
   *   0: no rotation
   *   1: 90 degrees clockwise
   *   2: 180 degrees
   *   3: 90 degrees counter clockwise
   */

//#########################################################################################
int pinCS = D6; 
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays   = 1;
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void StartMatrix(int rotationOfDisplays){
  matrix.setIntensity(MatrixIntensity);         // Use a value between 0 and 15 for brightness
  matrix.setRotation(0, rotationOfDisplays);    // The first display is position upside down
  matrix.setRotation(1, rotationOfDisplays);    // The first display is position upside down
  matrix.setRotation(2, rotationOfDisplays);    // The first display is position upside down
  matrix.setRotation(3, rotationOfDisplays);    // The first display is position upside down
  matrix.fillScreen(LOW);
  matrix.write();  
}

//#########################################################################################
void FlashMatrix(){
    matrix.drawChar(2,0, '0', HIGH,LOW,1); // H
    matrix.drawChar(8,0, '0', HIGH,LOW,1); // HH  
    matrix.drawChar(14,0,':', HIGH,LOW,1); // HH:
    matrix.drawChar(20,0,'0', HIGH,LOW,1); // HH:M
    matrix.drawChar(26,0,'0', HIGH,LOW,1); // HH:MM
    matrix.write(); // Send bitmap to display
    
  for (int inx = 0; inx <= 15; inx++) {
    matrix.setIntensity(inx);
    delay(100);
  }
  for (int inx = 15; inx >= 0; inx--) {
    matrix.setIntensity(inx);
    delay(60);
  }
  delay(500);
}

//#########################################################################################
char time_value[20];

void DispClock(){
  //  MatrixIntensity = map(analogRead(0),0,1024,0,12);

  matrix.setIntensity(MatrixIntensity);
  matrix.fillScreen(LOW);
  
  time_t now = time(nullptr);
  
  String time = String(ctime(&now));
  time.trim();

  time.substring(11,19).toCharArray(time_value, 10); 

  matrix.drawChar(2,0, time_value[0], HIGH,LOW,1); // H
  matrix.drawChar(8,0, time_value[1], HIGH,LOW,1); // HH

  if (time_value[7] % 2) {
    matrix.drawChar(14,0,time_value[2], HIGH,LOW,1); // HH:
  }
  else {
    matrix.drawChar(14,0,' ', HIGH,LOW,1); // HH:
  }
  
  matrix.drawChar(20,0,time_value[3], HIGH,LOW,1); // HH:M
  matrix.drawChar(26,0,time_value[4], HIGH,LOW,1); // HH:MM

  if (time_value[7] % 2) {
    matrix.drawChar(32,0,time_value[2], HIGH,LOW,1); // HH:MM:
  }
  else {
    matrix.drawChar(32,0,' ', HIGH,LOW,1); // HH:MM:
  }

  matrix.drawChar(38,0,time_value[6], HIGH,LOW,1); // HH:MM:S
  matrix.drawChar(44,0,time_value[7], HIGH,LOW,1); // HH:MM:SS

  matrix.write(); // Send bitmap to display
}

void DispClockP(){
  //  MatrixIntensity = map(analogRead(0),0,1024,0,12);

  matrix.setIntensity(MatrixIntensity);
  matrix.fillScreen(LOW);
  
  time_t now = time(nullptr);
  
  String time = String(ctime(&now));
  time.trim();

  time.substring(11,19).toCharArray(time_value, 10); 

  matrix.drawChar(2,0, time_value[0], HIGH,LOW,1); // H
  matrix.drawChar(8,0, time_value[1], HIGH,LOW,1); // HH
  matrix.drawChar(14,0,time_value[2], HIGH,LOW,1); // HH:
  matrix.drawChar(20,0,time_value[3], HIGH,LOW,1); // HH:M
  matrix.drawChar(26,0,time_value[4], HIGH,LOW,1); // HH:MM
  matrix.drawChar(32,0,time_value[2], HIGH,LOW,1); // HH:MM:
  matrix.drawChar(38,0,time_value[6], HIGH,LOW,1); // HH:MM:S
  matrix.drawChar(44,0,time_value[7], HIGH,LOW,1); // HH:MM:SS

  matrix.write(); // Send bitmap to display
}

//#########################################################################################
int wait = 90; // In milliseconds
int spacer = 1;  // dots between letters
int width  = 5 + spacer; // The font width is 5 pixels + spacer

void display_message(String message){
   for ( int i = 0 ; i < width * message.length() + matrix.width() - spacer; i++ ) {
    //matrix.fillScreen(LOW);
    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically
    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < message.length() ) {
        matrix.drawChar(x, y, message[letter], HIGH, LOW, 1); // HIGH LOW means foreground ON, background off, reverse to invert the image
      }
      letter--;
      x -= width;
    }
    matrix.write(); // Send bitmap to display
    delay(wait/2);
  }
}
