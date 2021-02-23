#define soundPin 34

const int sampleWindow = 50;
unsigned int sample;
int soundLevelLimit = 35;

#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxxxx"
//Define Firebase Data object
FirebaseData firebaseData;

#include <Wire.h>
#include "SSD1306.h" 
 
SSD1306  display(0x3c, 21, 22);


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

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

String sllCloudFull;
String sllCloud;
if(Firebase.getString(firebaseData,"IOTLAB/Sound_Level_Indicator/Sound_Level_Limit",sllCloudFull)){
sllCloud = sllCloudFull.substring(2,sllCloudFull.length()-2);
soundLevelLimit = sllCloud.toInt();
Serial.println(soundLevelLimit);
}
  
unsigned long startMillis = millis();
float peakToPeak =0;
unsigned int signalMax = 0;
unsigned int signalMin = 4095;

while(millis()-startMillis < sampleWindow)
{
  sample = analogRead(soundPin);
  
  
    if(sample > signalMax)
    {
      signalMax = sample;
    }
    else if(sample < signalMin)
    {
      signalMin = sample;
    }
}
   
   peakToPeak = signalMax - signalMin;
   //Serial.println(signalMin);
   
   //Serial.println(signalMax);
   
  // Serial.println(peakToPeak);
   float db = 20 * log10(peakToPeak);
   Serial.println(db);
  String soundLevel;
   Firebase.setFloat(firebaseData,"IOTLAB/Sound_Level_Indicator/Sound_Level_Value",db);
  
  String myString = "Loudness:";
  char buffer[6];
  dtostrf(db,5,1,buffer);
  myString.concat(buffer);
  myString.concat("dB");
  display.drawString(0,0,myString);
    
   
   if (db > soundLevelLimit)
    soundLevel="Talking";
    else
    soundLevel="Silence";
   
    Firebase.setString(firebaseData,"IOTLAB/Sound_Level_Indicator/Sound_Level_Class",soundLevel);
   display.drawString(0,30,soundLevel);
   display.display();
   delay(150);
}
