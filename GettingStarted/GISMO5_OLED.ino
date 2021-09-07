#include <Wire.h>
#include "SSD1306.h"

SSD1306 display(0x3c,21,22);
String myString;
int count;
void setup() {
  // put your setup code here, to run once:
display.init();
display.setFont(ArialMT_Plain_24);

}

void loop() {
  // put your main code here, to run repeatedly:
display.clear();
myString = "Hello   " + String(count);
display.drawString(0,0,myString);
display.display();
count++;
if(count==10) count=0;
delay(1000);
}
