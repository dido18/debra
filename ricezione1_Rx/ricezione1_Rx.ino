#include <Wire.h>
#include <VirtualWire.h>

//variabili Rx
#define BufferL 6
#define PinRx 12  // pin analogico di RX segnale
        
typedef union {
    byte ComByte[2];
    int MeasData;
} comdata;
        
comdata potenziom1;
comdata potenziom2;

char msg[BufferL];  
int pianto=1;     // segnale digitale digital pin 3. se è 1 non va niente. se arriva lo zero attiva if
             

int potenziometro2=0; 
int potenziometro1=1;

unsigned long LastM1 = 0;
unsigned long LastM2 = 0;

boolean S1 = false;
boolean S2 = false;


void setup(){   
  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  
  //inizializzazione var Rx
  potenziom1.MeasData=0; // segnale ingresso analogico 
  potenziom2.MeasData=0; // 
   
  Serial.begin(9600);                 // set up Serial library at 9600 bps
  TWBR = ((F_CPU /400000l) - 16) / 2; // Change the i2c clock to 400KHz
 
  //AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  //////////////////////////////////////////
  //RFcomm
  //vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_rx_pin(PinRx);        // set the analog pin of the WifiReceiver
  vw_setup(3000);              // Bits per sec
    
  vw_rx_start();       // Start the receiver PLL running
}

void loop(){
     //routine di ricezione dato
     RiceviDatoRadioF();
     //Serial.println(potenziom1.MeasData );
     
    //Azione da fare se arriva il segnale analogico del sensore di suono...i valori sono indicativi
    if(potenziom1.MeasData > 150 ){
      Serial.println("Davidino ti prendo a calci");
    } else  if(potenziom1.MeasData > 20 && potenziom1.MeasData<150) {
      Serial.println("e non ti lamentare"); 
    }
    
    //Azione da fare se arriva il segnale digitale del sensore di suono...
    if (pianto==0){
      Serial.println("e stai zitto");
    }
}
        
//routine di ricezione Rf
void RiceviDatoRadioF(void) {
  
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  //Serial.println("Ricezione dato");   
  if (vw_get_message(buf, &buflen)){ // Non-blocking 
       potenziom1.ComByte[0] = buf[2];//qui arriva il valore dell'ingresso analogico 0
       potenziom1.ComByte[1] = buf[3];//qui arriva il valore dell'ingresso analogico 0
       potenziom2.ComByte[0] = buf[4];
       potenziom2.ComByte[1] = buf[5];
       switch(buf[0]){   //il primo bit ricevuto definisce il comando (l'opzione???')
           case 0:// disattiva gli altri comandi ponendoli uguali a 1                         
           case 1:      
               pianto = buf[1];  //buf[1] sarà uguale a 0. mi attiva un if         
               break;
        
          }//fine switch selezione dato
      }//fine if ricezione dato 
} //end of RicaviDatoRadioF

