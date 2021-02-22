#define motorPin 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(13,HIGH);
delay(2000);
digitalWrite(motorPin,LOW);
delay(2000);
}
