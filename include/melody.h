/**
 * @file melody.h
 * @brief Contains the definition of the Melody class for playing musical tunes.
 *
 * This file declares the Melody class, which is used to control the playback of melodies
 * and rhythms using buzzers.
 */

#ifndef MELODY_H
#define MELODY_H

#include "buzzer.h"
#include <atomic>

/**
 * @class Melody
 * @brief Manages the playback of melodies and rhythms.
 *
 * This class handles the playing of melodies and rhythms through two buzzers. It allows
 * for starting, stopping, and toggling the playback of a musical tune.
 */
class Melody
{
public:
    /**
     * @brief Constructs a Melody object.
     *
     * @param melodyBuzzer Reference to the Buzzer object used for playing melody notes.
     * @param drumBuzzer Reference to the Buzzer object used for playing drum beats.
     */
    Melody(Buzzer &melodyBuzzer, Buzzer &drumBuzzer)
        : melodyBuzzer(melodyBuzzer), drumBuzzer(drumBuzzer) {}

    /**
     * @brief Plays a jingle using the melody and drum buzzers.
     *
     * @param melody Array of melody notes.
     * @param durations Array of note durations corresponding to the melody notes.
     * @param drumPattern Array of drum notes.
     * @param drumLength Length of the drum pattern array.
     * @param melodyLength Length of the melody array.
     */
    void playJingle(int melody[], int durations[], int drumPattern[], int drumLength, int melodyLength)
    {
        isPlaying.store(true);
        for (int thisNote = 0; thisNote < melodyLength && isPlaying.load(); thisNote++)
        {
            int noteDuration = 1000 / durations[thisNote];
            melodyBuzzer.playTone(melody[thisNote], noteDuration);

            if (thisNote < drumLength && drumPattern[thisNote] != 0)
            {
                drumBuzzer.playTone(drumPattern[thisNote], noteDuration);
            }

            delay(noteDuration * 1.30);
            melodyBuzzer.stopTone();
            drumBuzzer.stopTone();
        }
        isPlaying.store(false);
    }

    /**
     * @brief Stops the music playback.
     */
    void stopMusic()
    {
        isPlaying.store(false);
    }

    /**
     * @brief Toggles the music playback state.
     *
     * @return The new state of the music playback (true for playing, false for stopped).
     */
    bool toggleMusic()
    {
        bool currentState = isPlaying.load();
        isPlaying.store(!currentState);
        return !currentState;
    }

private:
    Buzzer &melodyBuzzer;        ///< Buzzer for playing melody notes.
    Buzzer &drumBuzzer;          ///< Buzzer for playing drum beats.
    std::atomic<bool> isPlaying; ///< Atomic flag indicating whether music is currently playing.
};

#endif // MELODY_H
