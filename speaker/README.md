

https://diyhacking.com/arduino-speaker/



# tone()
The program creates tones with a function, `tone( )`.

 It generates a square wave of the specified frequency (and 50% duty cycle) on a pin.
 A duration can be specified for this. Otherwise, the wave continues until a call to noTone().
 The Arduino pin can be connected to a piezo buzzer or other speakers to play the tones.

Syntax:
```
tone(pin, frequency)
tone(pin, frequency, duration)
```

Parameters
- `pin`: the pin on which to generate the tone
- `frequency`: the frequency of the tone in hertz – unsigned int
- `duration`: the duration of the tone in milliseconds (optional) – unsigned long

The code below uses an extra file, `pitches.h` This file contains all the pitch values for typical notes.
For example, NOTE_C4 is middle C. NOTE_FS4 is F sharp, and so forth.
So instead of writing the frequency in the tone( ) function, we’ll just have to write the name of the note. This note table was originally written by Brett Hagman, on whose work the tone() command was based. You may find it useful whenever you want to make musical notes for your Arduino speaker

# How I made melody[ ] and noteDurations[ ] of this song:
If you take a look at the program, you can find two int arrays It is similar to how ringtones were written in old Nokia cell phones.
- `melody[ ]`: The first array contains the notes
-  `noteDurations[ ]` and the second array contains its corresponding durations.

I found out the notes of this song with my guitar. I wrote down the musical notes of this song first and then wrote the melody[ ] array with that.

Then I wrote noteDurations[ ] according to the length of each music note.
Here 8 = quarter note, 4 = 8th note, etc.
Higher value gives longer duration notes.
The note and its corresponding duration is what is there in melody[ ] and noteDurations[ ] respectively.
You can modify those and create any song according to your wish!
