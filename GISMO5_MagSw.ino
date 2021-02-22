#define magSW 16
void setup() {
  // put your setup code here, to run once:
pinMode(magSW,INPUT_PULLUP);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  int sw_status;
  sw_status = digitalRead(magSW);
  if (sw_status)
  Serial.println("Switch open");
  else
  Serial.println("Switch closed");

  delay(1000);
  

}
