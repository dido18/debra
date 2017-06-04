
/*
 * beehibe.ino  (trasmitter / receiver)
 * 
 * Receives/trasmit the signals to the bee(s) sensors. 
 * 
 */

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <RHDatagram.h>    //manager 
#include <ArduinoJson.h>

const uint16_t speed = 2000; //The desired bit rate in bits per second
const uint8_t rxPin=11;
const uint8_t txPin=12;

#define BEE_QUEEN_ADDRESS 0


RH_ASK driver(speed, rxPin, txPin);

RHDatagram manager (driver, BEE_QUEEN_ADDRESS);


// byte operation  :  3 ;   // 3 bits operation
struct dataStruct {
  byte op : 3 ;       // 0 =register, 
  uint8_t  data ;   // 2 bytes with no negative numbers = 65,535 (2^16) - 1)
} message;



byte tx_buf[sizeof(message)] = {0};


void setup()
{
    Serial.begin(9600);   // Debugging only
    if (!manager.init())
         Serial.println("init failed");
}



void loop(){
    //rh_send();
    // rh_receive();
    recv_bee();
}

//uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];  // buffers for receieing  packet messages (max 60 bytes) 
//uint8_t buflen = sizeof(buf);

int value =0;
void recv_bee(){  
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];  // buffers for receieing  packet messages (max 60 bytes) 
  
  if (manager.available())
  {
    uint8_t buflen = sizeof(buf);
    uint8_t from;
    uint8_t to;
    if (manager.recvfrom(buf, buflen))//, &from, &to))
    {
        memcpy(&message, buf, sizeof(message));
//        Serial.print("got request from: ");
//        Serial.print(manager.headerFrom());
//        Serial.print("  to: ");
//        Serial.print(manager.headerTo()); //to
//        Serial.print("  Operation:");
//        Serial.print(message.op);
//        Serial.print(" Data: ");
//        Serial.println(message.data);

    // Serial response s JSON object
    StaticJsonBuffer<100> jsonBuffer;
    
    JsonObject& root = jsonBuffer.createObject();
    root["type"] = "monitor";  // "signal"
    root["status"] = "received";
    root["code"] = 9;     // manager.headerFrom();
    root["value"] = value;
    value = value + 1; 
    
    //send JSON to beehive (raspberry or pc)
    root.printTo(Serial);
    Serial.println();
            
    }
  }
  
}

void send_to_bee_from_serial(){
  if (Serial.available() > 0){
      String val = Serial.readStringUntil('\n');
       Serial.println(val);
        if (val)
        {
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();     
        }
   }
}
//void rh_send(){
//
////  Serial.println("Init Send");
////  memcpy(tx_buf, &message, sizeof(message) );
////  byte zize=sizeof(message);
////
////  driver.send((uint8_t *)tx_buf, zize);
////
////  driver.waitPacketSent();
////  Serial.println("End send");
//  //String val = Serial.readStringUntil('\n');
//  //Serial.println(val);
//  int val = 30;
//  if (val)
//  {
//
//    // send value towads "bee" 
//    //mySwitch.send(val.toInt(), 24);
//    
//
//    // Serial response
//    StaticJsonBuffer<100> jsonBuffer;
//    
//    JsonObject& root = jsonBuffer.createObject();
//    root["type"] = "signal";
//    root["status"] = "sent";
//    root["code"] = val;
//    
//    //send JSON to beehive
//    root.printTo(Serial);
//    Serial.println();
//  }
//  
//}


//void rh_receive(){
//    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];  // buffers for receieing  packet messages (max 60 bytes) 
//    uint8_t buflen = sizeof(buf);
//
//    
//    //Serial.println("CHECK receive");
//    if (manager.recv(buf, &buflen)) // Non-blocking, Turns the receiver on if it not already on. If there is a valid message available, copy it to buf and return true else return false.
//    {
//      //Serial.println("init receive");
//    
//      memcpy(&message, buf, sizeof(message));
//      // Message with a good checksum received, dump it.
//      //driver.printBuffer("Got:", buf, buflen);
//      
//      //Serial.println("End receive");
//      
//    }
//  
//}


