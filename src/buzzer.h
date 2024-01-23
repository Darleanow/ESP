#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
public:
    Buzzer(int pin) : buzzerPin(pin) {
        pinMode(buzzerPin, OUTPUT);
    }

    void playTone(int frequency, int duration) {
        tone(buzzerPin, frequency, duration);
    }

    void stopTone() {
        noTone(buzzerPin);
    }

private:
    int buzzerPin;
};

#endif // BUZZER_H
