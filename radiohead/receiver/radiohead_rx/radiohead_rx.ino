#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;
// default receiver digital pin 11

//RH_ASK::RH_ASK  ( uint16_t  speed = 2000,
//uint8_t   rxPin = 11,
//uint8_t   txPin = 12,
//uint8_t   pttPin = 10,
//bool  pttInverted = false 
//)   

struct dataStruct{
  unsigned int press_norm ; 
  float press_hg;
  float temp;
  unsigned long counter;
   
}message;

void setup()
{
    Serial.begin(9600); // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    driver.maxMessageLength (); 
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];  // buffers for receivein the packet (max 60 bytes) 
    uint8_t buflen = sizeof(buf);
    
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;

      // Message with a good checksum received, dump it.
      driver.printBuffer("Got:", buf, buflen);
      
      memcpy(&message, buf, sizeof(message));
      Serial.println("");
       
      Serial.print("press_norm: ");
      Serial.print(message.press_norm);
        
      Serial.print("  press_hg: ");
      Serial.print(message.press_hg);
        
      Serial.print("  temp: ");
      Serial.print(message.temp);
        
      Serial.print("  counter: ");
      Serial.println(message.counter);
    }
}

//    uint8_t buf[12];
//    uint8_t buflen = sizeof(buf);
//    if (driver.recv(buf, &buflen)) // Non-blocking
//    {
//      int i;
//      // Message with a good checksum received, dump it.
//      Serial.print("Message: ");
//      Serial.println((char*)buf);
//    }
// }
