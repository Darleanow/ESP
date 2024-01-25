#ifndef MELODY_H
#define MELODY_H

#include "Buzzer.h"
#include <atomic>

class Melody {
public:
    Melody(Buzzer& melodyBuzzer, Buzzer& drumBuzzer)
    : melodyBuzzer(melodyBuzzer), drumBuzzer(drumBuzzer) {}

    void playJingle(int melody[], int durations[], int drumPattern[], int drumLength, int melodyLength) {
        isPlaying.store(true);
        for (int thisNote = 0; thisNote < melodyLength && isPlaying.load(); thisNote++) {
            int noteDuration = 1000 / durations[thisNote];
            melodyBuzzer.playTone(melody[thisNote], noteDuration);

            if (thisNote < drumLength && drumPattern[thisNote] != 0) {
                drumBuzzer.playTone(drumPattern[thisNote], noteDuration);
            }

            delay(noteDuration * 1.30);
            melodyBuzzer.stopTone();
            drumBuzzer.stopTone();
        }
        isPlaying.store(false);
    }

    void stopMusic() {
        isPlaying.store(false);
    }

    bool toggleMusic() {
    bool currentState = isPlaying.load();
    isPlaying.store(!currentState);
    return !currentState;
}


private:
    Buzzer& melodyBuzzer;
    Buzzer& drumBuzzer;
    std::atomic<bool> isPlaying{false};
};

#endif // MELODY_H
