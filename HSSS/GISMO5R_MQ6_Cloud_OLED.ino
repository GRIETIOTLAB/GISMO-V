int magSWReading;
int gasThresholdDelta = 30;
int delayTiming;
bool gasLeakDetected;
int gasReading;
int prevGasReading;

#define magSW 16

#include <Wire.h>
#include "SSD1306.h" 

SSD1306  display(0x3c, 21, 22);


#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
//Define Firebase Data object
FirebaseData firebaseData;


void setup() {
  // put your setup code here, to run once:
  pinMode(magSW,INPUT_PULLUP);
  Serial.begin(115200);
  for(int i = 0;i < 2000; i++){
    gasReading = analogRead(36);
    Serial.print(".");
    prevGasReading = gasReading;
    delay(100);
  }

    //Connecting to Wi-Fi network
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
display.init();
display.setFont(ArialMT_Plain_16);

}

void loop() {
  // put your main code here, to run repeatedly:
  display.clear();
  gasReading = analogRead(36);
  if(gasReading-prevGasReading > gasThresholdDelta){
  gasLeakDetected = true;
  Serial.println("Gas Leak deteccted");
  Firebase.setInt(firebaseData,"IOTLAB/HSSS/Gas_Leak",1);
   display.drawString(0,0,"Gas Leak");
  }
  else{
  Firebase.setInt(firebaseData,"IOTLAB/HSSS/Gas_Leak",0);
   display.drawString(0,0,"Gas: OK");
  }
  Serial.println(gasReading);
  prevGasReading = gasReading;

  magSWReading = digitalRead(magSW);
  if(magSWReading == 0){
    Serial.println("Window open detected");
    Firebase.setInt(firebaseData,"IOTLAB/HSSS/Window_Open",1);
     display.drawString(0,30,"Window Open");
  }
  else{
  Firebase.setInt(firebaseData,"IOTLAB/HSSS/Window_Open",0);
   display.drawString(0,30,"Window: OK");

  }
  display.display();
  if(gasLeakDetected || !magSWReading)
  delay(3000);
  else
  delay(1000);

}
