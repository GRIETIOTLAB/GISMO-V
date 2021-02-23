#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
unsigned long delayTime;

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
Serial.println("--Default Test--");
delayTime = 1000;
Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
printValues();
delay(delayTime);
}

void printValues(){
  Serial.print("Temperature = ");
Serial.print(bme.readTemperature());
Serial.println(" deg C");

Serial.print("Temperature = ");
Serial.print(1.8*bme.readTemperature()+32);
Serial.println(" deg F");

Serial.print("Pressure = ");
Serial.print(bme.readPressure()/100.0F);
Serial.println(" hPa");

Serial.print("Altitude = ");
Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
Serial.println(" m");

Serial.print("Humidity = ");
Serial.print(bme.readHumidity());
Serial.println(" %");

Serial.println();

}
