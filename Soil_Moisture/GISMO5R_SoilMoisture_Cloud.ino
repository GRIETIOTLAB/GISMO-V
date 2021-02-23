/* Soil Moisture sensor pin   : GPIO34
 * Relay pin                  : GPIO13
 *
  */
#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxxx"
//Define Firebase Data object
FirebaseData firebaseData;

#define smPin 34
#define relayPin 13
int smValue;
int smLimit = 3000;
int delayTime = 2000;
String smValueCloud;
void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin,OUTPUT);
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
String smCloudFull;
String smCloud;
if(Firebase.getString(firebaseData,"IOTLAB/Smart_Garden/SM_Threshold",smCloudFull)){
smCloud = smCloudFull.substring(2,smCloudFull.length()-2);
smLimit = smCloud.toInt();
Serial.println(smLimit);
}
smValue = 4095 - analogRead(smPin);
Serial.print("Soil Moisture = ");
Serial.println(smValue);
Firebase.setInt(firebaseData,"IOTLAB/Smart_Garden/Soil_Moisture",smValue);

if (smValue < smLimit){
digitalWrite(relayPin,HIGH);
Serial.println("Motor turned ON");
Firebase.setString(firebaseData,"IOTLAB/Smart_Garden/Motor_Status","ON");
}
else{
digitalWrite(relayPin,LOW);
Serial.println("Motor turned OFF");

Firebase.setString(firebaseData,"IOTLAB/Smart_Garden/Motor_Status","OFF");
}

delay(delayTime);
}
