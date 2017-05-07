
#include <VirtualWire.h>

//inizializzazione variabili
//se il sensore del suono è digitale (cioè acceso o spento), collegarlo al pin digitale 3. altrimenti al pin analogico 0

//variabili Tx
#define BufferL 6   // length of the message (in bytes) 
#define PinTx 12    // pin TX on Wifi
        
typedef union {
    byte ComByte[2];
    int MeasData; 
} comdata; //massimo valore trasmissibile = +-32767;

comdata potenziom1;  //struttura dati inviata 
comdata potenziom2;

char msg[BufferL];  
        
//Create variables for each button on the Joystick Shield to assign the pin numbers
        
int potenziometro2=0;    //valore analogico letto dal potenziometro2
int potenziometro1=0;    //valore analogico letto dal potenziometro1
                
int opzione = 0;
int comando = 1;

void setup() {
  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  
  //inizializzaz tx vars
  potenziom1.MeasData = 0; // ritardo ciclo
  potenziom2.MeasData = 0; // ritardo ciclo

  Serial.begin(9600);     
  pinMode(13,OUTPUT);         //led blinking
  vw_set_ptt_inverted(true); 
  vw_set_tx_pin(PinTx);
  vw_setup(3000);             // speed of data transfer Kbps
  
}

void loop(){    
  LeggiPotenziometri();

  // messaggio in tx: msg[BufferL] = {opzione,comando,potenziom1Byte1,potenziom1Byte2,potenziom2Byte1,potenziom2Byte2};

  //da utilizzare se sensore suono è digitale.
  if (digitalRead(3)==0){
      //Serial.print("puopa");
      opzione =1;
      comando=0;
  }else{
      opzione =0;
      comando=1;
  }
        
  msg[0] = opzione;
  msg[1] = comando;
  msg[2] = potenziom1.ComByte[0];
  msg[3] = potenziom1.ComByte[1];
  msg[4] = potenziom2.ComByte[0];
  msg[5] = potenziom2.ComByte[1];
   
  //TX routine
  digitalWrite(13, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, BufferL);
  //Serial.print(vw_send((uint8_t *)msg, BufferL));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13, LOW);
  //delay(1000);
}

void LeggiPotenziometri(void){
  potenziometro1=analogRead(0);//da utilizzare se sensore suono è analogico
  potenziometro2=analogRead(1);//inutilizzato
     
  potenziom1.MeasData = potenziometro1;  //invio del valore del pin analogico 0
  potenziom2.MeasData = potenziometro2;  //
  //Serial.println(potenziom2.MeasData);
  //Serial.println(potenziom1.MeasData);

}//end of LeggiPotenziometri(void)

