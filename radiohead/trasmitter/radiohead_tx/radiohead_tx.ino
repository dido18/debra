#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

// pin of the TX
//#define PinTx 12
//#define ReadSoundPin 0

void setup()
{
    Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    const char *msg = "Hello World!";

    digitalWrite(13, HIGH); // Flash a light to show transmitting
    Serial.print("Sending..");

    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();

    digitalWrite(13, LOW);

    delay(1000);

}
