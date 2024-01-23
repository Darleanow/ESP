#ifndef MELODY_H
#define MELODY_H

#include "Buzzer.h"

class Melody {
public:
    Melody(Buzzer& melodyBuzzer, Buzzer& drumBuzzer)
    : melodyBuzzer(melodyBuzzer), drumBuzzer(drumBuzzer) {}

    void playJingle(int melody[], int durations[], int drumPattern[], int drumLength, int melodyLength) {
        for (int thisNote = 0; thisNote < melodyLength; thisNote++) {
            int noteDuration = 1000 / durations[thisNote];
            melodyBuzzer.playTone(melody[thisNote], noteDuration);

            if (thisNote < drumLength && drumPattern[thisNote] != 0) {
                drumBuzzer.playTone(drumPattern[thisNote], noteDuration);
            }

            delay(noteDuration * 1.30);
            melodyBuzzer.stopTone();
            drumBuzzer.stopTone();
        }
    }

private:
    Buzzer& melodyBuzzer;
    Buzzer& drumBuzzer;
};

#endif // MELODY_H
