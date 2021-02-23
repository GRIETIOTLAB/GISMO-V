#include <Wire.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);

#define motorPin 13

#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxx"
//Define Firebase Data object
FirebaseData firebaseData;

int delayTime = 2000;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin,OUTPUT);
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

String motorCmdFull;
String motorCmd;
int finalCmd;

display.clear();
Firebase.getString(firebaseData,"IOTLAB/Motor_Control/Motor_Cmd",motorCmdFull);
motorCmd = motorCmdFull.substring(2,motorCmdFull.length()-2);
finalCmd = motorCmd.toInt();

if(finalCmd == 1)
{
  digitalWrite(motorPin,HIGH);
  Serial.println("Motor ON");
  display.drawString(20,0,"MOTOR ON");
}
else
{
  digitalWrite(motorPin,LOW);
  Serial.println("Motor OFF");
  display.drawString(20,0,"MOTOR OFF");
  
}


display.display();  
delay(delayTime);
}
