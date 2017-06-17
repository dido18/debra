#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

// driver.maxMessageLength () = 60 bytes every message



struct dataStruct{
  unsigned int sound ;   // 2 bytes with no negative numbers = 65,535 (2^16) - 1)
  //float press_hg;
  //float temp;
  unsigned long counter;
   
}message;


byte tx_buf[sizeof(message)] = {0};

int sensorPin = A0;    // select the input anaolgo pin

const int middleValue = 90 ;  //512
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
     // long  = read_sound();
      //Serial.println(g);

 
     digitalWrite(13, HIGH); // Flash a light to show transmitting
//
     message.sound = 6400; //analogRead(sensorPin);  // read analog sound value
   Serial.println("Sound level");
    Serial.println(message.sound);
//
    memcpy(tx_buf, &message, sizeof(message) );
    //void * memcpy ( void * destination, const void * source, size_t num );
    // Copy block of memory
    // Copies the values of num bytes from the location pointed to by source directly to the memory block pointed to by destination.
    byte zize=sizeof(message);
//
    driver.send((uint8_t *)tx_buf, zize);
    Serial.print("Sending.....");
//
//    // driver.send((uint8_t *)msg, strlen(msg));
     driver.waitPacketSent();
//
    digitalWrite(13, LOW);
//    message.counter++;
//
    delay(1000);
//
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

