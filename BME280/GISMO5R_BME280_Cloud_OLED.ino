#include <Wire.h>
#include "SSD1306.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFi.h>
#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxx"
//Define Firebase Data object
FirebaseData firebaseData;
#define SEALEVELPRESSURE_HPA (1013.25)

SSD1306  display(0x3c, 21, 22);

Adafruit_BME280 bme;
unsigned long delayTime;

 float tempC,tempF,atPressure,altitude,humidity;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.println(F("BME280 test"));

bool status;

status = bme.begin(0x76);
if(!status){
  Serial.println("Could not find BME280 module");
  while(1);
}
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
Serial.println("--Default Test--");
delayTime = 2000;
Serial.println();

 display.init();
 display.setFont(ArialMT_Plain_16);
}

void loop() {
  // put your main code here, to run repeatedly:
printValues();
displayValues();
delay(delayTime);
}
   //Firebase.setFloat(firebaseData,"DHT11_Data/Temperature",temperature);
   

void printValues(){
 // float tempC,tempF,atPressure,altitude,humidity;
  Serial.print("Temperature = ");
  tempC = bme.readTemperature();
//Serial.print(bme.readTemperature());
Serial.print(tempC);
Serial.println(" deg C");
Firebase.setFloat(firebaseData,"IOTLAB/Environment_Monitor/Temperature",tempC);

Serial.print("Temperature = ");
//Serial.print(1.8*bme.readTemperature()+32);
Serial.print(1.8*tempC+32);
Serial.println(" deg F");

Serial.print("Pressure = ");
atPressure=bme.readPressure()/100.0F;
//Serial.print(bme.readPressure()/100.0F);
Serial.print(atPressure);
Serial.println(" hPa");
Firebase.setFloat(firebaseData,"IOTLAB/Environment_Monitor/Pressure",atPressure);

Serial.print("Altitude = ");
altitude=bme.readAltitude(SEALEVELPRESSURE_HPA);
//Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
Serial.print(altitude);
Serial.println(" m");
Firebase.setFloat(firebaseData,"IOTLAB/Environment_Monitor/Altitude",altitude);

Serial.print("Humidity = ");
humidity=bme.readHumidity();
//Serial.print(bme.readHumidity());
Serial.print(humidity);
Serial.println(" %");
Firebase.setFloat(firebaseData,"IOTLAB/Environment_Monitor/Humidity",humidity);

Serial.println();

}

void displayValues(){
  display.clear();
  
  String myString = "";
  
  char buffer[6];
  dtostrf(tempC,5,1,buffer);
  myString.concat(buffer);
  myString.concat(" C");
  display.drawString(0,0,myString);

  myString = "";
  dtostrf(humidity,5,1,buffer);
  myString.concat(buffer);
  myString.concat(" %");
  display.drawString(64,0,myString);

 myString = "";
  dtostrf(atPressure,5,1,buffer);
  myString.concat(buffer);
   display.drawString(0,30,myString);

    myString = "";
  dtostrf(altitude,5,1,buffer);
  myString.concat(buffer);
  myString.concat("m");
   display.drawString(64,30,myString);


  display.display();

}
