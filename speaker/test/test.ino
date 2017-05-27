/*Arduino speaker song tutorial
 * This program will play the theme song of the Malayalam movie
 * 'Ennu Ninte Moideen'. The song is 'Mukkathe Penne'.
 * The song is played on the speaker connected to pin 3 and GND.
 *
 * Created 26 Oct 2015
 * by Akshay James
 * Video at https://www.youtube.com/watch?v=LgtcUxe8fmA
 */

#include"pitches.h"

// notes in the song 'Mukkathe Penne'
int melody[] = {
  NOTE_C4,  NOTE_D4, NOTE_E4,
  NOTE_B0, 0, NOTE_B2, NOTE_B3, NOTE_B4, NOTE_B5, NOTE_B6, NOTE_B7,
  NOTE_C1, NOTE_C2, NOTE_C3, NOTE_C4, NOTE_C5, NOTE_C6, NOTE_C7,
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4,
  NOTE_E4, NOTE_F4, NOTE_G4, 
  NOTE_E4, NOTE_F4, NOTE_G4,
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4, 
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4, 
  NOTE_D4, NOTE_G3, NOTE_C4,
  NOTE_D4, NOTE_G3, NOTE_C4,

  END

//  NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
//  NOTE_G4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4,      //29               //8
//  NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
//  NOTE_C4, NOTE_D4,0,
//
//  NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
//  NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5,
//  NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_FS4, NOTE_D5, NOTE_C5,
//  NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_AS4,             //58
//
//  NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
//  NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_G4,
//  NOTE_A4, 0, NOTE_AS4, NOTE_A4, 0, NOTE_G4,
//  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, 0,
//
//  NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
//  NOTE_C4, NOTE_D4, 0,
//  NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
//  NOTE_C4, NOTE_D4, END

};

// note durations: 
// 16 = 1
// 8= quarter note (1/4), 
// 4= 8th note (1/2)
// 2 = 1/8
int noteDurations[] = {       //duration of the notes
  3,3,3,
  8,8,8,8,8,8,8,8, // do, re, mi, do
  8,8,8,8,8,8,8, // do, re, mi, do
  4,4,4,4, // do, re, mi ,do
  4,4,8,    // mi, fa, sol
  4,4,8,   // mi, fa ,sol
  2,2,2,2,4,8,  // sol, la, sol, fa, mi, do
  2,2,2,2,4,8,  // sol, la, sol, fa, mi, do
  4,4,8,       // re, sol, do
  4,4,8       // re, sol, do
//
//  8,4,8,4,
//  4,2,1,1,2,1,1,12,
//  4,4,4,4,4,4,
//  4,16,4,
//
//  4,4,4,4,4,4,
//  4,4,4,12,
//  4,4,4,4,4,4,
//  4,4,4,12,
//
//  4,4,4,4,4,4,
//  2,1,1,2,1,1,4,8,4,
//  2,6,4,2,6,4,
//  2,1,1,16,4,
//
//  4,8,4,4,4,
//  4,16,4,
//  4,8,4,4,4,
//  4,20,
};

int speed=90;  //higher value, slower notes
void setup() {

  Serial.begin(9600);
  for (int thisNote = 0; melody[thisNote]!=-1; thisNote++) {

    int noteDuration = speed*noteDurations[thisNote];
    tone(3, melody[thisNote],noteDuration*.95);
    Serial.println(melody[thisNote]);

    delay(noteDuration);

    noTone(3);
  }
}

void loop() {
  // no need to repeat the melody.
}
