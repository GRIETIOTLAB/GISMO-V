#include "DHTesp.h"
#define DHTpin 27
DHTesp dht;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println("Status\tHumidity(%)\tTemperature(C)");

  dht.setup(DHTpin,DHTesp::DHT11);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  
 delay(2000);
  float h = dht.getHumidity();
  float t = dht.getTemperature();

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(h);
  Serial.print("\t");
  Serial.println(t);
  
  

}
