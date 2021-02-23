#include "DHTesp.h"
#define DHTpin 27
DHTesp dht;
int delayTime = 2000;

#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxx"
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
  

}

void loop() {
  // put your main code here, to run repeatedly:

  
 delay(delayTime);
  float h = dht.getHumidity();
  float t = dht.getTemperature();

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(h);
  Firebase.setFloat(firebaseData,"IOTLAB/Ambient_Parameters/Humidity",h);
  Serial.print("\t");
  Serial.println(t);
  Firebase.setFloat(firebaseData,"IOTLAB/Ambient_Parameters/Temperature",t);
  
  
}
