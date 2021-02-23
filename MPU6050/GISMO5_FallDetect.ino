#include "I2Cdev.h"
#include "MPU6050.h"

#include "Wire.h"
MPU6050 mpu;


float baseline[3];
float features[3];
float motion_threshold = 0.7;


void setup() {
  
    Wire.begin();
    Serial.begin(115200);
    mpu.initialize();
    calibrate();  
      
    
   }

void loop() {
   
    float ax,ay,az; 
    mpu_read(&ax,&ay,&az);
    ax=ax-baseline[0];
    ay=ay-baseline[1];
    az=az-baseline[2];
   
    mpu_record();

    
 delay(2000);
     
  }
  
void mpu_read(float *ax,float *ay,float *az) {
    int16_t _ax, _ay, _az, _gx, _gy, _gz;

    mpu.getMotion6(&_ax, &_ay, &_az, &_gx, &_gy, &_gz);
    *ax = _ax/16384.0;
    *ay = _ay/16384.0;
    *az = _az/16384.0;
        
}



void calibrate(){
  float ax,ay,az;
  for(int i=0;i < 10;i++){
    mpu_read(&ax,&ay,&az);
    delay(100);
      }
  baseline[0]=ax;
  baseline[1]=ay;
  baseline[2]=az;
}

 

void mpu_record(){
  float ax,ay,az;
  float aax,aay,aaz;
  String position;
    mpu_read(&ax,&ay,&az);
    ax = ax - baseline[0];
    ay = ay - baseline[1];
    az = az - baseline[2];

   features[0] = ax;
   features[1] = ay;
   features[2] = az;

  Serial.print(features[0]);
  Serial.print(" ");
  Serial.print(features[1]);
  Serial.print(" ");
  Serial.println(features[2]);
  
  aax=fabs(ax);
  aay=fabs(ay);
  aaz=fabs(az);

  Serial.print(aax);
  Serial.print(" ");
  Serial.print(aay);
  Serial.print(" ");
  Serial.println(aaz);
  
  position="Upright";
  if(aax > motion_threshold)
  {
    if(ax > 0)
    position="Left";
    else
    position="Right";
  }
  if(aay > motion_threshold)
  {
    if(ay > 0)
    position="Backward";
    else
    position="Forward";
  }
  

   
  Serial.println(position);
  
  
  
  }
