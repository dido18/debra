# DEBRA

## Hardware
Specifications RF 433MHz Receiver

- Frequency Range: 433.92 MHz
- Modulation: ASK
- Input Voltage: 5V
- Price: $1 to $2

Specifications RF 433MHz Transmitter
- Frequency Range: 433.92MHz
- Input Voltage: 3-12V


## Comunicazione wireless
Verrà utilizzato il modulo wireless low-cost che funziona sulle frequenze 433 MHz. Il suo nome è **MX-05V** e **MX-FS-03V**.


Library for 433Mhz transmission with Arduino:
- [**VirtualWire  (deprecated)**](http://www.airspayce.com/mikem/arduino/VirtualWire/):VirtualWire is no longer maintained and it seems to be quite sensitive to radio interference.
-  [**RadioHead**](http://www.airspayce.com/mikem/arduino/RadioHead/) (new version of VirtualWire) RadioHead for example is quite big and has an unnecessary dependency on the SPI library

    - [Tutorial](http://randomnerdtutorials.com/rf-433mhz-transmitter-receiver-module-with-arduino/)

    - [ASK driver](http://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html) is a Driver for Arduino, Maple and others that provides features to send short messages, without addressing, retransmit or acknowledgment, a bit like UDP over wireless, using ASK (amplitude shift keying). Supports a number of inexpensive radio transmitters and receivers. All that is required is transmit data, receive data and (for transmitters, optionally) a PTT transmitter enable. Can also be used over various analog connections (not just a data radio), such as the audio channel of an A/V sender, or long TTL lines.
- [**Rc-switch**](https://github.com/sui77/rc-switch):  is optimized to be compatible with remote controlled light or mains switches and is not really suitable for the transmission of arbitrary data packets.
    -[](https://sites.google.com/site/summerfuelrobots/arduino-sensor-tutorials/rf-wireless-transmitter-receiver-module-433mhz-for-arduino)
- [**New library (not well testes)**](https://andreasrohner.at/posts/Electronics/New-Arduino-library-for-433-Mhz-AM-Radio-Modules/)
  - [Receiver](https://github.com/zeitgeist87/RFReceiver)

Tutorials:
- [ismanettone- virtualwire](http://ismanettoneblog.altervista.org/blog/lezione-12-comunicazioni-wireless-low-cost-arduino/?doing_wp_cron=1493236840.0937430858612060546875)


## Arduino Libro
- *livello TTL** codifica di 0 con 0 volt, 1 con  5 Volt (3,3 volt)

#### Tipi di dato

| Tipo          	| Byte 	| Intervallo              	| note                                                       	|
|---------------	|------	|-------------------------	|------------------------------------------------------------	|
| int           	| 2    	| -32768:32767            	| Numero di bit varua dalla piattaforma (arduino sono 16bit) 	|
| unsigned int  	| 2    	| 0:65535                 	| Solo numero positivi                                       	|
| long          	| 4    	| -2147483648: 2147483647 	|                                                            	|
| unsigned long 	| 4    	| 0:                      	|                                                            	|
| float         	| 4    	|                         	|                                                            	|
| double        	| 4    	|                         	|                                                            	|
| boolean       	| 1    	| 0(false) 1(false)       	|                                                            	|
| char          	| 1    	| -128:127                	|                                                            	|
| byte          	| 1    	| 0:255                   	|                                                            	|


Arduino, byte, uint8_t and unsigned short can be used interchangeably because they are literally the same type.  It’s just an alias. If you are just compiling the sketch on Arduino IDE and upload to the Arduino, use byte should be enough.


- A *byte* stores an 8-bit unsigned number, from 0 to 255. For example for the number 0, the binary form is 00000000, there are 8 zeros (8 bits in total). for the number 255, the binary form is 11111111.

- *uint8_t* data type is basically the same as byte in Arduino. Writers of embedded software often define these types, because systems can sometimes define int to be 8 bits, 16 bits or 32 bits long. The issue doesn’t arise in C# or Java, because the size of all the basic types is defined by the language.

- An *unsigned char* data type that occupies 1 byte of memory. It is the same as the byte datatype. The unsigned char datatype encodes numbers from 0 to 255. For consistency of Arduino programming style, the byte data type is to be preferred.



#### Spostatre i bit
- Spostare i bit con arduino è molto più veloce che dividere o moltiplicare

```
int x  = 6;       // 0000000 00000110
int res = x << 1; // 0000000 00001100 -> 6 spostato a sinistra di una posizione diventa  12   
int res = x << 2  // 0000000 00011000 -> 6 spostato a sinistra di due posizione diventa 24 (16+8):
```

- `<< n` :  uguale a moltiplicare il valore per 2 elevato alla potenza di n

- `>> n` :  uguale a dividere il valore per 2 elevato alla potenza di n

#### Estrarre  i byte alti e bassi in un int o in un long
- utile quando si vuole inviare un `int` (2 byte) su una porta seriale,
- `lowByte(i)`:  estrae il byte meno significativo di un intero
- `highByte(i)`: estrae il byte più significativo di un intero

```
int intValue = 128;            // 00000001 00000010

byte lowByte, highByte;

lowByte = lowByte(intValue);   //  00000010
Serial.println(lowByte, DEC)   //  2       -> byte basso

highByte = highByte(intValue); // 00000001
Serial.println(highByte, DEC)  // 1        -> byte alto

```

#### Formare un int o un long con byte alti e bassi
- utile quando si ricevono valori interi in forma di byte singoli su una porta seriale.
- creare un int a 16 bit (int) o a 32 bit (long) partendo da singoli byte
- `word(h,l)` converte due byte in un solo valore a 16 bit.
- (da controllare) Arduino non permette da long a 32 bit in due word da 16 bit.

```
int intValue = 258;                  // 00000001 00000010
byte lowByte = lowByte(intValue);   //  00000010
Serial.println(lowByte, DEC)        //  2       -> byte basso
byte highByte = highByte(intValue); // 00000001
Serial.println(highByte, DEC)       // 1        -> byte alto

int loWord;
loWord = word(highByte, lowByte); // converte i byte in una word (int)


```

#### Comunicazioni Seriali
- per Comunicazioni facili e flessibili tra arduino e pc e altri dispositivi
- Arduino è dotato di un chip che converte la porta seriale hardware in USB
- Arduino dispone di una sola porta seriale hardware (comunicazone seriale può essere emulata ma sono più lenti)


```
void setup(){
  Serial.begin(9600)  // velocità di comunicazone in baud (bit per secondo)
                      // 1000 caratter al secondo
                      // deve essere uguale all velocità impostata sul serial monito
                      // nell'IDE di arduino
}

int number

void loop{
  Serial.println("the number is");
  Serial.println(number);
}
```

**Inviare** ad arduino i comandi tramite porta seriale (dal pc)

- `Serial` riceve valori a 8 bit

```
void loop(){
  if (Serial.available()){
    char ch = Serial.read(){
      if( isDigit(ch)){  // single digit from '0' to '9'
               blinkRate = (ch - '0')  // converte ASCII in valore numerico
      }
    }
  }
}

```


*ASCII* caratteri to numeri:
      - '0'-'9' hanno codici ASCII tra 48 - 57
      - '0' ha valore ASCII 48
      - per ottenere 1 =
### inviare dati binari da arduino
- invio in formato binario per ridurre numero di byte oppure perche l'applicazione gestisci solo dati binario
- con i dati binari ( adifferenza delle stringhe) si deve definire dove il messaggio inzia e dove finsce

- trasmettitore e ricettore devono sapere esattamenet quanti byte vengono inviati.
- si invio un valore che indica quanti byte seguiranno
- ATTENZIONE: le due parti possono avere dimensioni di tipi di dato diverse (in java an int is 4 byte, arduino naint is 2 byte)

Inviare un intero da arduino si inviano il byte basso e alto che lo compongonao
```
Serial.write(lowByte(intValue),BYtE)
Serial.write(highByte(intValue),BYTE)

```  
