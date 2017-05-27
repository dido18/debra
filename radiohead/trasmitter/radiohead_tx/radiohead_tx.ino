#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

// driver.maxMessageLength () = 60 bytes every message

//  Default TX pin is 12



struct dataStruct{
  unsigned int sound ;   // 2 bytes with no negative numbers = 65,535 (2^16) - 1)
  //float press_hg;
  //float temp;
  unsigned long counter;
   
}message;


byte tx_buf[sizeof(message)] = {0};

int sensorPin = A0;    // select the input anaolgo pin

void setup()
{
    pinMode(A0, INPUT);
    Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");

}

void loop()
{
    digitalWrite(13, HIGH); // Flash a light to show transmitting

    message.sound = analogRead(sensorPin);  // read analog sound value
    Serial.println("Sound level");
    Serial.println(message.press_norm);

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

