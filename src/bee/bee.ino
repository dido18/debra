#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

/*
 * bee.ino  (trasmitter)
 * 
 * It has a analog sound sensor and the code are sent to the beehive.
 * 
 * 
 */

RH_ASK driver;


struct dataStruct{
  long  sound ;   // 2 bytes with no negative numbers = 65,535 (2^16) - 1)
  //float temp;  
}message;


byte tx_buf[sizeof(message)] = {0};

int sensorPin = A0;    // Input analog pin of the sound sensor

const int middleValue = 90 ;      //512
const int numberOfSamples = 128; // how many reads every cycle
int sample;                      // value of the michopone read every time
long segnale;

long averageReading;

long runningAverage = 0;
const int averageOver = 16;

void setup()
{
    pinMode(A0, INPUT);
    Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");

}

void loop()
{
     
    message.sound = read_sound();      // read sound level with 128 sample each cycle. 
    digitalWrite(13, HIGH);            // Flash a light to show transmitting

    memcpy(tx_buf, &message, sizeof(message) );
    byte zize=sizeof(message);

    driver.send((uint8_t *)tx_buf, zize);

    driver.waitPacketSent();

    digitalWrite(13, LOW);
    
    delay(10000);

}



long  read_sound()
{
  long sumOfSquares = 0;
  for (int i =0; i < numberOfSamples ; i++)
  {
    sample = analogRead(sensorPin);
    //Serial.println(sample);
    segnale = (sample - middleValue);  // calculate the shift from the middle value
    segnale *= segnale;  // power the signal for having positive values
    sumOfSquares += segnale;
  }

  averageReading = sumOfSquares/numberOfSamples;                // actual average
  runningAverage = (((averageOver-1)*runningAverage)+averageReading)/averageOver; //

  //Serial.println(runningAverage);
  return runningAverage;
}
