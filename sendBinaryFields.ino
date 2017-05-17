
# invia valori dei pin digitali en analogoi in dati binari

const chat HEASER = 'H'  // Header di un carattere che indica l'inizio del messaggio

void setup(){

  Serial.begin(9600);
  for (int i=2; i<= 13; i++){
    pinMode(i,INPUT)  // pin form 2 to 13 as INPUT
    digitalWrite(i, HIGH)   // accende tutte le resistenze pull-up

  }


void loop(){
  Serial.write(HEADER)

  int values  =0;
  int bit = 0;
  for (int i=2; i<= 13; i++){
    bitWrite(values, bit, digitalRead(i))  // imposta il bit su 0 o su 1 a seconda
    //che il valore del dato pin incrementa o decrementa
    bit = bit +1;

  }

  ///+

  sendBinary(values);
  for (int i=0; i<= 6; i++){
      values = analogRead(i);
      sendBinary(values); // invia il numero

  }
}

void sendBinary(int value){
  Serial.write(lowByte(value));
  Serial.write(highByte(value))
}
