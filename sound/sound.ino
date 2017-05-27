

void setup()
{
  Serial.begin(9600); // open serial port, set the baud rate at 9600 bps
  pinMode(A0, INPUT);
}
void loop()
{
      int val;
      val=analogRead(A0);   //connect mic sensor to Analog 0
      Serial.println(val,DEC);// print the sound value to serial monitor       
      delay(100);
}
