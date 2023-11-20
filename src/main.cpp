#include <Arduino.h>
#include <microDS18B20.h>
#include "./notes.h"

int buzzer = 32;  // the pin that the buzzer is attached to
int buzzer2 = 33; // the second buzzer
int sensor = 26;  // the pin that the sensor is attached to
int state = LOW;  // by default, no motion detected
int val = 0;      // variable to store the sensor status (value)

void setup()
{
  pinMode(buzzer, OUTPUT); // initialize buzzer as an output
  pinMode(sensor, INPUT);  // initialize sensor as an input
  Serial.begin(115200);    // initialize serial
}

void playJingle(int melody[], int durations[], int drumPattern[], int drumLength, int melodyLength);

void loop()
{
  val = digitalRead(sensor); // read sensor value
  delay(1000);
  if (val == HIGH)
  { // check if the sensor is HIGH
    if (state == LOW)
    {
      Serial.println("Motion detected!");

      // Mario theme melody
      int melody[] = {
          NOTE_E7, NOTE_E7, 0, NOTE_E7,
          0, NOTE_C7, NOTE_E7, 0,
          NOTE_G7, 0, 0, 0,
          NOTE_G6, 0, 0, 0};

      // Durations for the Mario theme melody
      int durations[] = {
          12, 12, 12, 12,
          12, 12, 12, 12,
          12, 12, 12, 12,
          12, 12, 12, 12};

      // Simple drum beat
      int drumPattern[] = {NOTE_C2, 0, NOTE_C2, 0, NOTE_C2, 0, NOTE_C2, 0};
      playJingle(melody, durations, drumPattern, sizeof(drumPattern) / sizeof(drumPattern[0]), sizeof(melody) / sizeof(melody[0]));
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

void playJingle(int melody[], int durations[], int drumPattern[], int drumLength, int melodyLength)
{
  for (int thisNote = 0; thisNote < melodyLength; thisNote++)
  {
    int noteDuration = 1000 / durations[thisNote];
    tone(buzzer2, melody[thisNote], noteDuration);

    // Play drum sound on the second buzzer
    if (thisNote < drumLength)
    {
      if (drumPattern[thisNote] != 0)
      {
        tone(buzzer, drumPattern[thisNote], noteDuration);
      }
    }

    delay(noteDuration * 1.30);
    noTone(buzzer);  // stop the tone playing
    noTone(buzzer2); // stop the drum tone
  }
}
