#include <Arduino.h>
#include "./notes.h"

int buzzer = 27; // the pin that the buzzer is attached to
int sensor = 26; // the pin that the sensor is attached to
int state = LOW; // by default, no motion detected
int val = 0;     // variable to store the sensor status (value)

void setup()
{
  pinMode(buzzer, OUTPUT); // initialize buzzer as an output
  pinMode(sensor, INPUT);  // initialize sensor as an input
  Serial.begin(115200);    // initialize serial
}

void playJingle(int notes[], int durations[]);

void loop()
{
  val = digitalRead(sensor); // read sensor value
  if (val == HIGH)
  { // check if the sensor is HIGH
    if (state == LOW)
    {
      Serial.println("Motion detected!");
      playJingle(lavandia_melody, lavandia_noteDurations);
      state = HIGH; // update variable state to HIGH
    }
  }
  else
  {
    if (state == HIGH)
    {
      Serial.println("Motion stopped!");
      state = LOW; // update variable state to LOW
    }
  }
}

void playJingle(int notes[], int durations[])
{
  for (int thisNote = 0; thisNote < 28; thisNote++)
  {
    int noteDuration = 1000 / durations[thisNote];
    tone(buzzer, notes[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzer); // stop the tone playing
  }
}
