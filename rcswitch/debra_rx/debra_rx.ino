#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  //  Digital Pins With Interrupts
  //The first parameter to attachInterrupt is an interrupt number.
  //Normally you should use digitalPinToInterrupt(pin) to translate the actual digital pin to the specific interrupt number. 
  // For example, if you connect to pin 3, use digitalPinToInterrupt(3) as the first parameter to attachInterrupt.
  //Board  Digital Pins Usable For Interrupts
  //Uno, Nano, Mini, other 328-based  PIN: 2, 3 
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  Serial.println("DEBRA - completed setup");

}

void loop() {
  
  if (mySwitch.available()) {
    //Serial.println("Switch is available");
    
    int value = mySwitch.getReceivedValue();

// telecomando universale code send A
//    Decimal: 5592512 (24Bit) Binary: 010101010101010111000000 Tri-State: FFFFFFFF1000 PulseLength: 361 microseconds Protocol: 1
//Raw data: 11204,316,1124,1044,408,240,1124,1048,408,312,1124,1044,412,312,1124,1044,412,312,1128,1040,412,312,1128,1040,412,312,1124,1044,412,312,1116,1048,408,1048,404,1052,404,316,1120,320,1120,312,1124,316,1124,316,1120,316,1124,


    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
    }

    mySwitch.resetAvailable();
  }

}
