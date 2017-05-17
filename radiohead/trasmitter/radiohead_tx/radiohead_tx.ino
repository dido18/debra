#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

//   pin of the TX
//  #define PinTx 12
//  #define ReadSoundPin 0


struct dataStruct{
  unsigned int press_norm ;   // 2 bytes with no negative numbers = 65,535 (2^16) - 1)
  float press_hg;
  float temp;
  unsigned long counter;
   
}message;


byte tx_buf[sizeof(message)] = {0};

void setup()
{
    Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");

    message.press_norm=65535; 
    message.press_hg=0.59; 
    message.temp=22.394; 

   
//    uint8_t maxMessage= driver.maxMessageLength ();  //Returns the maximum message length available in this Driver. 60 bytes = 30 unsigned int
//    Serial.println(maxMessage);
//    
//    Serial.println(sizeof(maxMessage));  // 60 bytes
//    int value = 4;
//    Serial.println(sizeof(value));
}

void loop()
{
    //const char *msg = "Hello World!";
    digitalWrite(13, HIGH); // Flash a light to show transmitting

    memcpy(tx_buf, &message, sizeof(message) );
    //void * memcpy ( void * destination, const void * source, size_t num );
    // Copy block of memory
    // Copies the values of num bytes from the location pointed to by source directly to the memory block pointed to by destination.
    byte zize=sizeof(message);

    driver.send((uint8_t *)tx_buf, zize);
    Serial.print("Sending.....");

    // driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();

    digitalWrite(13, LOW);
    message.counter++;

    delay(1000);

}

