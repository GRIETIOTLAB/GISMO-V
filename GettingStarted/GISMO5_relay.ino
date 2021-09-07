#define relayPin 13
void setup() {
  // put your setup code here, to run once:
pinMode(relayPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(relayPin,HIGH);
delay(1000);
digitalWrite(relayPin,LOW);
delay(1000);
}
