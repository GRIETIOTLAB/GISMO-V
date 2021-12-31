#include "Credentials.h"
#define magSwitch 16
#define Tag "IOTLAB/Test_Proj/Switch_Status"
int sensorStatus;

void setup() {
  // put your setup code here, to run once:
 sensorInit();
 WiFiConnect();
 displayInit();
 FBInit();
 
}

void loop() {
  // put your main code here, to run repeatedly:
    sensorStatus = sensorRead();
    Serial.println(sensorStatus);
    displayUpdate();
    FBUpdate();
    delay(2000);
    
}
void sensorInit(){
  pinMode(magSwitch,INPUT_PULLUP);
  Serial.begin(115200);
}
void displayInit(){
 display.init();
 display.setFont(ArialMT_Plain_16);

}
void WiFiConnect(){
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
 }
 void FBInit(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

 }
int sensorRead(){
  int sensorValue = digitalRead(magSwitch);
  return sensorValue;
}

void displayUpdate(){
  String myString = "SW : ";
  myString = myString + String(sensorStatus);
  display.drawString(0,0,myString);
  display.display();
}
void FBUpdate(){
  Firebase.setString(firebaseData,Tag,String(sensorStatus));
}
