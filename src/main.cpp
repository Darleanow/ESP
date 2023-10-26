#include <Arduino.h>

// put function declarations here:
// int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  // int result = myFunction(2, 3);
  Serial.begin(115200);
  pinMode(27, OUTPUT);
}

void loop() {
  // Vary the LED brightness by changing the PWM duty cycle
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(27, brightness);  // Set the LED brightness
    delay(10);  // Wait for a short time
  }
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(27, brightness);  // Set the LED brightness
    delay(10);  // Wait for a short time
  }
}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }