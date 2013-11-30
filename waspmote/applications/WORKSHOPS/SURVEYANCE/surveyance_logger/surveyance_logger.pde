#define SENSOR_PIN ANALOG1

int delay_reading = 500;
int reading = 0;
char reading_buff[20];

// define folder and file to store data
char* logfile="log.csv";


void setup() {
  
  USB.ON();
  
  SD.ON();
  //SD.mkdir(path);

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
  
   
}


void loop() {
  
  //PWR ON SENSOR
  PWR.setSensorPower(SENS_3V3,SENS_ON);
  Utils.setLED(LED1, LED_ON);

  //READ VALUE
  reading = analogRead(SENSOR_PIN);
  delay(delay_reading / 2);
  
  //PWR OFF SENSOR
  Utils.setLED(LED1, LED_OFF);
  PWR.setSensorPower(SENS_3V3,SENS_OFF);
  
  //WRITE DATA TO FILE (may need some convertion here...)
  Utils.long2array(reading, reading_buff);
  SD.appendln(logfile, reading_buff);
  
  USB.println(reading_buff);
  
  delay(delay_reading / 2);
}

