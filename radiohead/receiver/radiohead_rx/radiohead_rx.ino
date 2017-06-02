#include <RH_ASK.h>
#include <SPI.h>      // Not actualy used but needed to RH_ASK
#include "pitches.h"   // notes defintion with 

#include "framartino.h"  // melody[], noteDurations[] 



// default receiver digital pin 11

//RH_ASK::RH_ASK  ( uint16_t  speed = 2000,
//uint8_t   rxPin = 11,
//uint8_t   txPin = 12,
//uint8_t   pttPin = 10,
//bool  pttInverted = false 
//)   

#define pinRx 11           // digital pin wireless receiver
#define pinSpeaker 3         // digital pin speaker  output

#define maxSoundLevel  100   // max sound level received for starting the song



RH_ASK driver(2000, pinRx);



struct dataStruct{
  unsigned int sound ; 
  // float press_hg;
  // float temp;
  unsigned long counter;
   
}message;

void setup()
{
    Serial.begin(9600); // Debugging only

    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];  // buffers for receivein the packet (max 60 bytes) 
    uint8_t buflen = sizeof(buf);
    
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      
      memcpy(&message, buf, sizeof(message));
      
      Serial.println(""); 
      Serial.print("sound: ");
      Serial.print(message.sound);

      Serial.print("  counter: ");
      Serial.println(message.counter);
      
      if (message.sound < maxSoundLevel)
      {
        Serial.println("values < 100");
      }
      else // if (message.sound >= 100)
      {
        Serial.println("values >= 100");
        play_music();

      }
 
    }
}

void play_music()
{
  
  int speed=180;  //higher value, slower notes
  for (int thisNote = 0; melody[thisNote]!=-1; thisNote++) {

    int noteDuration = speed*noteDurations[thisNote];
    tone(pinSpeaker, melody[thisNote],noteDuration*.95);
    Serial.println(melody[thisNote]);

    delay(noteDuration);

    noTone(pinSpeaker);
  }


}

