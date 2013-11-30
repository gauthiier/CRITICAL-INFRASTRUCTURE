#define SENSOR_PIN ANALOG2

int delay_reading = 100;
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
  
  // RTC
  RTC.ON();
   
}


void loop() {
  
  Utils.setLED(LED1, LED_ON);
  
  float temp = RTC.getTemperature();
  
  Utils.float2String(temp, reading_buff, 3);
      
  delay(delay_reading / 2);
  
  //PWR OFF SENSOR
  Utils.setLED(LED1, LED_OFF);

  SD.appendln(logfile, reading_buff);
  
  USB.println(reading_buff);
  
  delay(delay_reading / 2);
}

