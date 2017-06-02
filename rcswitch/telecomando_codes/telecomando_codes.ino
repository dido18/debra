#include <RCSwitch.h>

/*
 * TELECOMANDO PER CANCELLO AUTOMATICO UNIVERSALE A 433,92 MHZ CAME, FADINI
 *  4 euro su amazon
 * 
 * Procedura per programmazione codici del telecomdndo:
 *  1) concellazione memoria esistente i) premere contemporaneamente A e B (lampeggio 3 volte) ii) senza lasciare A, rilasciare B, iii) sempre senza lasciare A, premere 3 volte B fino a che il led lampeggia in maniera constante.
 *  2) esecuzione del programma: variabile "code" conteine il codice inviao, quando arriva a zero tenere premuto il tasto da programmare
 * 
 */
// pin of the TX
#define PinTx 12

RCSwitch mySwitch = RCSwitch();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // TX is connected to arduino Pin #12
  mySwitch.enableTransmit(PinTx);

  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Pulse length of the  telecomando universal 
   mySwitch.setPulseLength(361);
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
}

void loop() {
  Serial.print("20");
  delay(10000);
  Serial.print("10");
  delay(10000);
  Serial.print("9");
  delay(1000);
  Serial.print("8");
  delay(1000);
  Serial.print("7");
  delay(1000);
  Serial.print("6");
  delay(1000);
  Serial.print("5");
  delay(1000);
  Serial.print("4");
  delay(1000);
  Serial.print("3");
  delay(1000);
  Serial.print("2");
  delay(1000);
  Serial.print("1");
  delay(1000);
  Serial.print("0");
  
  while (true){
   int code = 6003;
   mySwitch.send(code, 24); //6000 codice A
   Serial.print("Sending code: "+code);
  }
   
}
