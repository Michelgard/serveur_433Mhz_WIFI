/*
  Example for different sending methods
  
  https://github.com/sui77/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

  // Optional set pulse length.
  mySwitch.setPulseLength(320);
  
  // Optional set protocol (default is 1, will work for most outlets)
   mySwitch.setProtocol(1);
  
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(15);
  
}

void loop() {

  /* See Example: TypeA_WithDIPSwitches 
  mySwitch.switchOn("11111", "00010");
  delay(1000);
  mySwitch.switchOn("11111", "00010");
  delay(1000);*/

  /* Same switch as above, but using decimal code */
  mySwitch.send(1381719, 24);
  delay(1000);  
  mySwitch.send(1381716, 24);
  delay(1000);  
  
   /* Same switch as above, but using decimal code */
  mySwitch.send(4028049, 24);
  delay(1000);  
  //mySwitch.send(4028049, 24);
  //delay(1000); 

  /* Same switch as above, but using binary code 
  mySwitch.send("000000000001010100010001");
  delay(1000);  
  mySwitch.send("000000000001010100010100");
  delay(1000);*/

  /* Same switch as above, but tri-state code 
  mySwitch.sendTriState("00000FFF0F0F");
  delay(1000);  
  mySwitch.sendTriState("00000FFF0FF0");
  delay(1000);*/ 

  delay(2000);
}
