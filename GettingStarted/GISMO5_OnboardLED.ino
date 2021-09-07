#define onboardLED 2
void setup() {
  // put your setup code here, to run once:
pinMode(onboardLED,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(onboardLED,HIGH);
  delay(1000);
  digitalWrite(onboardLED,LOW);
  delay(1000);
}
