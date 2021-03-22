#define lockPin 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(lockPin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(lockPin,HIGH);
delay(2000);
digitalWrite(lockPin,LOW);
delay(2000);
}
