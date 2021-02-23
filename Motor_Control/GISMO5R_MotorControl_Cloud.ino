#define motorPin 13

#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxxxxx"
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
   
}

void loop() {
  // put your main code here, to run repeatedly:

String motorCmdFull;
String motorCmd;
int finalCmd;
Firebase.getString(firebaseData,"IOTLAB/Motor_Control/Motor_Cmd",motorCmdFull);
motorCmd = motorCmdFull.substring(2,motorCmdFull.length()-2);
finalCmd = motorCmd.toInt();
Serial.println(finalCmd);

if(finalCmd == 1)
{
  digitalWrite(motorPin,HIGH);
  Serial.println("Motor ON");
}
else
{
  digitalWrite(motorPin,LOW);
  Serial.println("Motor OFF");

  
}


  
delay(2000);
}
