/*
   bee.ino  (trasmitter)

   It has a analog sound sensor and the code are sent to the beehive.


*/

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <RHDatagram.h>    //manager 


const uint16_t speed = 2000; //The desired bit rate in bits per second
const uint8_t rxPin = 11;
const uint8_t txPin = 12;

#define BEE_ADDRESS 1
#define BEE_QUEEN_ADDRESS 0

RH_ASK driver(speed, rxPin, txPin);

RHDatagram manager (driver, BEE_ADDRESS);

struct dataStruct {
  byte  op : 3 ;       // 0 =register,
  uint8_t  data ;   // 2 bytes with no negative numbers = 65,535 (2^16) - 1)
} message;




byte tx_buf[sizeof(message)] = {0};

//int sensorPin = A0;    // Input analog pin of the sound sensor
//
//const int middleValue = 90 ;      //512
//const int numberOfSamples = 128; // how many reads every cycle
//int sample;                      // value of the michopone read every time
//long segnale;
//
//long averageReading;
//
//long runningAverage = 0;
//const int averageOver = 16;

void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);   // Debugging only
   if (!manager.init())
    Serial.println("init failed");

}

int data = 0;
void loop()
{
    send_msg_beequeen();
    delay(10000);
}

void send_msg_beequeen()
{
  message.op = 4;
  message.data = 100; //data;

  // data += 1;

  memcpy(tx_buf, &message, sizeof(message) );
  byte zize = sizeof(message);
  
  if (manager.sendto((uint8_t *)tx_buf, zize, BEE_QUEEN_ADDRESS))
  {

    Serial.print("Message sent to Bee queen");
    Serial.println(message.op);
    Serial.println(message.data);
  }
  else
  {
    Serial.print("Message NOT snet to Bee queen");
  }
  manager.waitPacketSent( ) ;
  Serial.print("sent message!");
}

//
//  //message.sound = read_sound();      // read sound level with 128 sample each cycle.
//  digitalWrite(13, HIGH);            // Flash a light to show transmitting
//
//
//  message.op = 1;
//  message.data = data;
//
//  data = data + 1;
//
//  memcpy(tx_buf, &message, sizeof(message) );
//  byte zize = sizeof(message);
//
//  driver.send((uint8_t *)tx_buf, zize);
//
//  driver.waitPacketSent();
//
//  digitalWrite(13, LOW);
//
//  delay(10000);



//
//long  read_sound()
//{
//  long sumOfSquares = 0;
//  for (int i = 0; i < numberOfSamples ; i++)
//  {
//    sample = analogRead(sensorPin);
//    //Serial.println(sample);
//    segnale = (sample - middleValue);  // calculate the shift from the middle value
//    segnale *= segnale;  // power the signal for having positive values
//    sumOfSquares += segnale;
//  }
//
//  averageReading = sumOfSquares / numberOfSamples;              // actual average
//  runningAverage = (((averageOver - 1) * runningAverage) + averageReading) / averageOver; //
//
//  //Serial.println(runningAverage);
//  return runningAverage;
//}
