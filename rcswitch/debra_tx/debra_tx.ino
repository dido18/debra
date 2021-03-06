#include <RCSwitch.h>

// pin of the TX
#define PinTx 12
#define ReadSoundPin 0

RCSwitch mySwitch = RCSwitch();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // TX is connected to arduino Pin #12
  mySwitch.enableTransmit(PinTx);

  pinMode(13,OUTPUT);         //led blinking
  
   // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
   mySwitch.setPulseLength(361);
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
}

void loop() {
  // Switch on:
  // The first parameter represents the setting of the first 5 DIP switches. 
  // In this example it's ON-ON-ON-ON-ON.
  // The second parameter represents the setting of the last 5 DIP switches. 
  // In this example the last 5 DIP switches are OFF-OFF-OFF-ON-OFF.  
  
  // mySwitch.switchOn("11111", "00010");
  //delay(1000);
  ///mySwitch.switchOff("11111", "00010");
  //delay(1000);

  digitalWrite(13, HIGH); // Flash a light to show transmitting
  //Serial.print("Sending..");
  //mySwitch.send(analogRead(ReadSoundPin), 24);
  //mySwitch.send(5592513, 24); //5592512
  //delay(2000); 
  
  digitalWrite(13, LOW); // Flash a light to show transmitting

//  /* Same switch as above, but using decimal code */
//  mySwitch.send(5393, 24);
//  delay(1000);  
//  mySwitch.send(5396, 24);
//  delay(1000);  

   

// send code A telecomando universale
//mySwitch.send("010101010101010111000000");
//
//  /* Same switch as above, but using binary code (5393) */
//  mySwitch.send("000000000001010100010001");
//  delay(1000);  
//  // send in binary code (5396)
//  mySwitch.send("000000000001010100010100");
//  delay(1000);
//
//  /* Same switch as above, but tri-state code */ 
//  mySwitch.sendTriState("00000FFF0F0F");
//  delay(1000);  
//  mySwitch.sendTriState("00000FFF0FF0");
//  delay(1000);
//
//  delay(20000);

}
