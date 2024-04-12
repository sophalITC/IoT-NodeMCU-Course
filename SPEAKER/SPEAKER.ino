int pinTone = D7;
void setup()
{
  analogWrite(pinTone,255);
  delay(1000);
}
void loop() 
{
  analogWriteFreq(262);
  delay(500);
  analogWriteFreq(294);
  delay(500);
  analogWriteFreq(330);
  delay(500);
  analogWriteFreq(349);
  delay(500);
  analogWriteFreq(392);
  delay(500);
  analogWriteFreq(440);
  delay(500);
  analogWriteFreq(494);
  delay(500);
  analogWriteFreq(523);
  delay(500);
}

