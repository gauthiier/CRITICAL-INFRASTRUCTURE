#include <WaspSensorPrototyping_v20.h>

int delay_reading = 500;

char reading_buff[20];

// define folder and file to store data
char* logfile="log.csv";

void setup() {
  
  USB.ON();
  
  SD.ON();

  // delete file
  if(SD.del(logfile)) {
    USB.println(F("file deleted"));
  } else {
    USB.println(F("file NOT deleted"));
  }
  
  // create file
  if(SD.create(logfile)) {
    USB.println(F("file created"));
  } else {
    USB.println(F("file NOT created"));
  }
  
  delay(100);
  
  // Sensor board
  SensorProtov20.ON();
  // RTC
  RTC.ON();
   
}


void loop() {
  
  Utils.setLED(LED1, LED_ON);
  
  float adc = SensorProtov20.readADC();
  
  Utils.float2String(adc, reading_buff, 6);
      
  delay(delay_reading / 2);
  
  Utils.setLED(LED1, LED_OFF);

  SD.appendln(logfile, reading_buff);
  
  USB.println(reading_buff);
  
  delay(delay_reading / 2);
}

