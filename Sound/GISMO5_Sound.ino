#define soundPin 34

const int sampleWindow = 50;
unsigned int sample;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
unsigned long startMillis = millis();
float peakToPeak =0;
unsigned int signalMax = 0;
unsigned int signalMin = 4095;

while(millis()-startMillis < sampleWindow)
{
  sample = analogRead(soundPin);
  
  
    if(sample > signalMax)
    {
      signalMax = sample;
    }
    else if(sample < signalMin)
    {
      signalMin = sample;
    }
}
   
   peakToPeak = signalMax - signalMin;
   //Serial.println(signalMin);
   
   //Serial.println(signalMax);
   
  // Serial.println(peakToPeak);
   float db = 20 * log10(peakToPeak);
   Serial.println(db);
   delay(150);
}
