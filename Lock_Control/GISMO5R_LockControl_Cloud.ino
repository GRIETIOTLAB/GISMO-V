
#define lockPin 13

#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxxxx"
//Define Firebase Data object
FirebaseData firebaseData;

int delayTime = 2000;

void setup() {
  // put your setup code here, to run once:
  pinMode(lockPin,OUTPUT);
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

String lockCmdFull;
String lockCmd;
int finalCmd;


Firebase.getString(firebaseData,"IOTLAB/Lock_Control/Validation_Status",lockCmdFull);
lockCmd = lockCmdFull.substring(2,lockCmdFull.length()-2);
finalCmd = lockCmd.toInt();
Serial.println(finalCmd);

if(finalCmd == 1)
{
  digitalWrite(lockPin,LOW);
  Serial.println("Lock OPEN");

}
else
{
  digitalWrite(lockPin,HIGH);
  Serial.println("Lock CLOSED");


}


delay(2000);
}
