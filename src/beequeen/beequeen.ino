#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

/*
 * beehibe.ino  (trasmitter / receiver)
 * 
 * Receives/trasmit the signals to the bee(s) sensors. 
 * 
 */

const uint16_t speed = 2000; //The desired bit rate in bits per second
const uint8_t rxPin=11;
const uint8_t txPin=12;


RH_ASK driver(speed, rxPin, txPin);


struct dataStruct{
  long  sound ;   // 2 bytes with no negative numbers = 65,535 (2^16) - 1)
  //float temp;  
}message;


byte tx_buf[sizeof(message)] = {0};


void setup()
{
    Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}



void loop(){
    rh_send();
    rh_receive();
}

void rh_send(){

  Serial.println("Init Send");
  memcpy(tx_buf, &message, sizeof(message) );
  byte zize=sizeof(message);

  driver.send((uint8_t *)tx_buf, zize);

  driver.waitPacketSent();
  Serial.println("End send");
  
}


void rh_receive(){
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];  // buffers for receieing  packet messages (max 60 bytes) 
    uint8_t buflen = sizeof(buf);
    
    Serial.println("CHECK receive");
    if (driver.recv(buf, &buflen)) // Non-blocking, Turns the receiver on if it not already on. If there is a valid message available, copy it to buf and return true else return false.
    {
      Serial.println("init receive");
    
      memcpy(&message, buf, sizeof(message));
      // Message with a good checksum received, dump it.
      //driver.printBuffer("Got:", buf, buflen);
      
      Serial.println("End receive");
      
    }
  
}


