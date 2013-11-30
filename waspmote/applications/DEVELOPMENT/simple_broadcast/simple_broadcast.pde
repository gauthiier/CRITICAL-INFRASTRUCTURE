     
#include <WaspXBee802.h>
#include <WaspFrame.h>    // CRITICAL INFRASTRUCTURE Frames defined in WaspFrame.h -- github --- XXXX

/*
CRITICAL INFRASTRUCTURE {values}:
SENSOR_CI0     <int>
SENSOR_CI1     <int>
SENSOR_CI2     <int>
SENSOR_CI3     <int>
SENSOR_CI4     <int>
*/

#define SENSOR_PIN ANALOG1 // PIN for the ADC reading

// declare ADC reading variable
int delay_reading = 500;
int reading = 0;


// declare packet
packetXBee* packet;

// mac address of this mote
char macHigh[10];
char macLow[11];


void setup() {
    
  // blink
  Utils.setLED(LED0, LED_ON);
  Utils.setLED(LED1, LED_ON);
  delay(2000);
  Utils.setLED(LED0, LED_OFF);
  Utils.setLED(LED1, LED_OFF);
  
  // setup radio + MAC
  xbee802.ON();
  delay(1000);
  xbee802.flush();
  
  // Get the XBee MAC address
  int counter = 0;
  while((xbee802.getOwnMac()!=0) && (counter<12))
  {
    xbee802.getOwnMac();
    counter++;
  }

  // convert mac address from array to string
  Utils.hex2str(xbee802.sourceMacHigh, macHigh, 4);
  Utils.hex2str(xbee802.sourceMacLow,  macLow,  4);  

  // DEBUG: print MAC to console  
  USB.ON();
  USB.print("mac address:");
  USB.print(macHigh);
  USB.println(macLow);
  USB.OFF();   
  
  //B.0 set mote id (16-Byte max)
  //frame.setID("CRITICAL-0");	    

}


void loop() {

// A. ADC READING 
  
  //A.1 PWR ON SENSOR
  PWR.setSensorPower(SENS_3V3,SENS_ON);
  Utils.setLED(LED1, LED_ON);

  //A.2 READ VALUE
  reading = analogRead(SENSOR_PIN);
  
  //A.3 PWR OFF SENSOR
  PWR.setSensorPower(SENS_3V3,SENS_OFF);
  
// B. BROADCAST PACKET

  //B.1 create ASCII frame
  frame.createFrame(ASCII,"CRITICAL-0");
    
  //B.1.1 add CRITICAL INFRASTRUCTURE sensor descriptors
  frame.addSensor(SENSOR_MAC, macLow);                // MAC
  frame.addSensor(SENSOR_CI0, reading);               // CI0 <------------------------- IMPORTANT! (see nomenclature in the header of this file)
  frame.addSensor(SENSOR_BAT, PWR.getBatteryLevel()); // Battery level
  
  //DEBUG: print frame to console
  frame.showFrame();
  
  //B.2 create packet
  packet=(packetXBee*) calloc(1,sizeof(packetXBee));   // memory allocation
  packet->mode=BROADCAST;                              // set Broadcast mode
  
  //B.3 send packet
  // radio ON
  xbee802.ON();  
  // sets Destination parameters [000000000000FFFF -> Broadcast]
  xbee802.setDestinationParams(packet, "000000000000FFFF", frame.buffer, frame.length); 
  // send 
  xbee802.sendXBee(packet);
  
  //B.4 check status (DEBUG)
  if(xbee802.error_TX == 0) {
    USB.println(F("TX OK"));
  } else {
    USB.println(F("TX ERROR"));
  }
  
  //B.5 free memory
  free(packet);
  packet = NULL;
  
//C. Delay

  delay(1000);

}

