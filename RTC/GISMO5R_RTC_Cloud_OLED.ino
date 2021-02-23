#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;
#include "SSD1306.h" 
SSD1306  display(0x3c, 21, 22);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#include "FirebaseESP32.h"
#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxxxxxxxxxx"
//Define Firebase Data object
FirebaseData firebaseData;

#define relayPin 13

int delayTime = 3000;

void setup() {
  // put your setup code here, to run once:
 pinMode(relayPin,OUTPUT);
  Serial.begin(115200);
  if(!rtc.begin()){
    Serial.print("No RTC module found");
    while(1);
  }

     //Connecting to Wi-Fi network
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  
  

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

 display.init();
 display.setFont(ArialMT_Plain_16);

}

void loop() {
  // put your main code here, to run repeatedly:
   display.clear();
   char buffer[10];
   DateTime now = rtc.now();
  /* Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();*/
    
    sprintf(buffer,"%02d-%02d-%02d",now.hour(),now.minute(),now.second());
    Serial.println(buffer);
    
    Firebase.setString(firebaseData,"IOTLAB/Appliance_Control/Current_Time",buffer);

    display.drawString(0,0,buffer);
   
   int currentTimeTotal;
   currentTimeTotal = now.hour()*60 + now.minute();
   Serial.println(currentTimeTotal);
    
   String startTimeFull;
   String startTime;
   int startTimeHrs,startTimeMins,startTimeTotal;
   Firebase.getString(firebaseData,"IOTLAB/Appliance_Control/Start_Time",startTimeFull);
   startTime=startTimeFull.substring(2,startTimeFull.length()-2);
   //Serial.println(startTime);
   display.drawString(0,30,startTime);
   startTimeHrs = startTime.substring(0,2).toInt();
   //Serial.println(startTimeHrs);
   startTimeMins = startTime.substring(3).toInt();
   //Serial.println(startTimeMins);
   startTimeTotal=startTimeHrs*60 + startTimeMins;
   Serial.println(startTimeTotal);


   String endTimeFull;
   String endTime;
   int endTimeHrs,endTimeMins,endTimeTotal;
   Firebase.getString(firebaseData,"IOTLAB/Appliance_Control/End_Time",endTimeFull);
   endTime=endTimeFull.substring(2,endTimeFull.length()-2);
   //Serial.println(endTime);
    display.drawString(80,30,endTime);
   endTimeHrs = endTime.substring(0,2).toInt();
   //Serial.println(endTimeHrs);
   endTimeMins = endTime.substring(3).toInt();
   //Serial.println(endTimeMins);
   endTimeTotal=endTimeHrs*60 + endTimeMins;
   Serial.println(endTimeTotal); 

   if((currentTimeTotal >= startTimeTotal) && (currentTimeTotal < endTimeTotal)){
    digitalWrite(relayPin,HIGH);
    Serial.println("Appliance ON"); 
    display.setColor(WHITE);
    display.drawCircle(60, 36, 8);
    display.fillCircle(60,36,8);
    Firebase.setInt(firebaseData,"IOTLAB/Appliance_Control/Appliance_Status",1);
   }
   else{
    digitalWrite(relayPin,LOW);
    Serial.println("Appliance OFF");
    display.setColor(BLACK);
    display.drawCircle(60, 36, 8);
    display.fillCircle(60,36,8);
    display.setColor(WHITE);
    display.drawCircle(60, 36, 8);
    Firebase.setInt(firebaseData,"IOTLAB/Appliance_Control/Appliance_Status",0);
    }

   
   
  display.display();   
  delay(delayTime); 

}
