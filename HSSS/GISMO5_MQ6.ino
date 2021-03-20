int magSWReading;
int gasThresholdDelta = 30;
int delayTiming;
bool gasLeakDetected;
int gasReading;
int prevGasReading;

#define magSW 16
void setup() {
  // put your setup code here, to run once:
  pinMode(magSW,INPUT_PULLUP);
  Serial.begin(115200);
  for(int i = 0;i < 2000; i++){
    gasReading = analogRead(36);
    Serial.print(".");
    prevGasReading = gasReading;
    delay(100);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  gasReading = analogRead(36);
  if(gasReading-prevGasReading > gasThresholdDelta){
  gasLeakDetected = true;
  Serial.println("Gas Leak deteccted");
  }
  Serial.println(gasReading);
  prevGasReading = gasReading;

  magSWReading = digitalRead(magSW);
  if(magSWReading == 0){
    Serial.println("Window open detected");
  }
  delay(1000);

}
