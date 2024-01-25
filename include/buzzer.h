/**
 * @file Buzzer.h
 * @brief Contains the definition of the Buzzer class.
 *
 * This file declares the Buzzer class, which is used for controlling a buzzer attached
 * to an ESP32 or similar microcontroller. It provides methods to play and stop tones.
 */

#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

/**
 * @class Buzzer
 * @brief Manages a buzzer for playing tones.
 *
 * This class encapsulates the functionality of a buzzer. It provides methods to play
 * a tone at a specific frequency and duration, and to stop the tone.
 */
class Buzzer
{
public:
    /**
     * @brief Constructs a Buzzer object.
     *
     * @param pin The microcontroller pin to which the buzzer is connected.
     */
    Buzzer(int pin) : buzzerPin(pin)
    {
        pinMode(buzzerPin, OUTPUT);
    }

    /**
     * @brief Plays a tone through the buzzer.
     *
     * @param frequency The frequency of the tone in hertz.
     * @param duration The duration to play the tone in milliseconds.
     */
    void playTone(int frequency, int duration)
    {
        tone(buzzerPin, frequency, duration);
    }

    /**
     * @brief Stops any tone currently being played through the buzzer.
     */
    void stopTone()
    {
        noTone(buzzerPin);
    }

private:
    int buzzerPin; ///< The microcontroller pin to which the buzzer is connected.
};

#endif // BUZZER_H
