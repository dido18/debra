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

}

void loop() {
  
  if (mySwitch.available()) {
    //Serial.println("Switch is available");
    
    int value = mySwitch.getReceivedValue();
    
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
