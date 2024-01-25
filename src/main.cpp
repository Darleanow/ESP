/**
 * @file main.cpp
 * @brief Main entry point for the ESP32 web server and sensor application.
 *
 * This file contains the setup and loop functions for an ESP32-based system, which
 * integrates a motion sensor, buzzers for playing melodies, and a web server for remote control.
 */

#include "sensor.h"
#include "buzzer.h"
#include "melody.h"
#include "server.h"
#include "mario.h"

Sensor motionSensor(26); ///< Motion sensor connected to pin 26.

/**
 * @brief Toggles the motion detection state.
 *
 * This function is a callback used for toggling the motion sensor's state
 * from the web server.
 */
void toggleMotionDetection()
{
    motionSensor.toggleState();
}

Buzzer buzzer(32), buzzer2(33);       ///< Buzzers connected to pins 32 and 33.
Melody melodyPlayer(buzzer2, buzzer); ///< Melody player using the two buzzers.

/**
 * @brief Toggles the music playback state.
 *
 * @return The new state of the music playback (true for playing, false for stopped).
 */
bool toggleMusic()
{
    return melodyPlayer.toggleMusic();
}

server_web webServer("Formation", "Et@@g210573", 80, &toggleMotionDetection, toggleMusic); ///< Web server instance.

/**
 * @brief Setup function for initializing components.
 *
 * This function is called once when the program starts. It initializes the serial communication,
 * the web server, and other components.
 */
void setup()
{
    Serial.begin(115200);
    webServer.begin(); // Initialize the web server
}

/**
 * @brief Main loop of the program.
 *
 * Continuously checks for and handles incoming web server clients. It also checks the state
 * of the motion sensor and plays a melody if motion is detected.
 */
void loop()
{
    webServer.handleClient(); // Handle web server clients

    // Check if motion is detected and the sensor is active
    if (motionSensor.isMotionDetected() && motionSensor.getState())
    {
        Serial.println("Motion detected!");
        int drumPattern[] = {NOTE_C2, 0, NOTE_C2, 0, NOTE_C2, 0, NOTE_C2, 0}; // Drum pattern for the melody
        melodyPlayer.playJingle(melody, durations, drumPattern, sizeof(drumPattern) / sizeof(drumPattern[0]), sizeof(melody) / sizeof(melody[0]));
    }
}
