#include <Wire.h>
#include "SSD1306.h" 
 
SSD1306  display(0x3c, 21, 22);

float t = 32.0;
float h = 55.6;
  
 
void setup() {
 display.init();
 display.setFont(ArialMT_Plain_24);
}
 
void loop() {
  display.clear();
  String myString = "T = ";
  char buffer[6];
  dtostrf(t,5,1,buffer);
  myString.concat(buffer);
  myString.concat(" C");
  display.drawString(0,0,myString);
  myString = "H = ";
  dtostrf(h,5,1,buffer);
  myString.concat(buffer);
  myString.concat(" %");
  display.drawString(0, 30,myString);
  display.display();
  delay(1000);
  t=t+0.1;
  h=h+0.1;
  }
