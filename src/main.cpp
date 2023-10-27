#include <Arduino.h>

const int ledPin = 27;

void setup()
{
  // Initialize serial communication
  Serial.begin(115200);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void fadeLED(int startBrightness, int endBrightness, int step, int delayTime)
{
  for (int brightness = startBrightness; brightness != endBrightness; brightness += step)
  {
    analogWrite(ledPin, brightness);
    delay(delayTime);
  }
}

void loop()
{
  // Fade LED from off to full brightness
  fadeLED(0, 256, 1, 10);

  // Fade LED from full brightness to off
  fadeLED(255, -1, -1, 10);
}
