#include <Wire.h>
#include "SSD1306.h" 

#include "DHTesp.h"
#define DHTpin 27
DHTesp dht;
int delayTime = 2000;

SSD1306  display(0x3c, 21, 22);

#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxxxx"
//Define Firebase Data object
FirebaseData firebaseData;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println("Status\tHumidity(%)\tTemperature(C)");

  dht.setup(DHTpin,DHTesp::DHT11);

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
display.setFont(ArialMT_Plain_24);
}

void loop() {
  // put your main code here, to run repeatedly:

  
 delay(delayTime);
  float h = dht.getHumidity();
  float t = dht.getTemperature();
  String myString;
  char buffer[6];

  display.clear();
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(h);
  Firebase.setFloat(firebaseData,"IOTLAB/Ambient_Parameters/Humidity",h);
  
  myString="H = ";
  dtostrf(h,5,1,buffer);
  myString.concat(buffer);
  myString.concat(" %");
  display.drawString(0,0,myString);
  
  Serial.print("\t");
  Serial.println(t);
  Firebase.setFloat(firebaseData,"IOTLAB/Ambient_Parameters/Temperature",t);
  
  myString="T = ";
  dtostrf(t,5,1,buffer);
  myString.concat(buffer);
  myString.concat(" C");
  display.drawString(0,30,myString);
  display.display();
}
