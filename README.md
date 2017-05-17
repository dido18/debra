# DEBRA DEtection Baby Radio Access

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
    -[Tutorial] (http://randomnerdtutorials.com/rf-433mhz-transmitter-receiver-module-with-arduino/)
    -[ASK driver](http://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html) is a Driver for Arduino, Maple and others that provides features to send short messages, without addressing, retransmit or acknowledgment, a bit like UDP over wireless, using ASK (amplitude shift keying). Supports a number of inexpensive radio transmitters and receivers. All that is required is transmit data, receive data and (for transmitters, optionally) a PTT transmitter enable. Can also be used over various analog connections (not just a data radio), such as the audio channel of an A/V sender, or long TTL lines.
- [**Rc-switch**](https://github.com/sui77/rc-switch):  is optimized to be compatible with remote controlled light or mains switches and is not really suitable for the transmission of arbitrary data packets.
    -[](https://sites.google.com/site/summerfuelrobots/arduino-sensor-tutorials/rf-wireless-transmitter-receiver-module-433mhz-for-arduino)
- [**New library (not well testes)**](https://andreasrohner.at/posts/Electronics/New-Arduino-library-for-433-Mhz-AM-Radio-Modules/)
  - [Receiver](https://github.com/zeitgeist87/RFReceiver)

Tutorials:
- [ismanettone- virtualwire](http://ismanettoneblog.altervista.org/blog/lezione-12-comunicazioni-wireless-low-cost-arduino/?doing_wp_cron=1493236840.0937430858612060546875)

## Trasmit message

 The 3,5,4,20 define the number of bits assigned to each element in the structure so only 32 bits (4 bytes) are used.

// The MESSAGE being Sent over wireless
struct Message {
  byte operation  :  3 ;   // P for Publish / S-set G-get value
  byte locationID :  5 ;   // Defines a Location In House
  byte measure    :  4 ;   // What are we measuring
  long value      : 20 ;   // The value we observed
} message;





