#include <WiFi.h>
#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxxxxxxxx"
//Define Firebase Data object
FirebaseData firebaseData;

#define ledPin 2
void setup() {
  // put your setup code here, to run once:
pinMode(ledPin,OUTPUT);
Serial.begin(115200);
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
  String ledCmdFull;
String ledCmd;
int finalCmd;
Firebase.getString(firebaseData,"IOTLAB/My_App/Motor_Cmd",ledCmdFull);
ledCmd = ledCmdFull.substring(2,ledCmdFull.length()-2);
finalCmd = ledCmd.toInt();
Serial.println(finalCmd);

if(finalCmd == 1)
{
  digitalWrite(ledPin,HIGH);
  Serial.println("LED ON");
}
else
{
  digitalWrite(ledPin,LOW);
  Serial.println("LED OFF");

  
}  
  delay(1000);
} 
