#include "sensor.h"
#include "buzzer.h"
#include "melody.h"
#include "server.h"
#include "mario.h"

Sensor motionSensor(26);

// FIXME: PLEASE FOR FUCK SAKE ENZO
void toggleMotionDetection()
{
    motionSensor.toggleState();
}

Buzzer buzzer(32), buzzer2(33);
Melody melodyPlayer(buzzer2, buzzer);

bool toggleMusic()
{
    return melodyPlayer.toggleMusic();
}

server_web webServer("Formation", "Et@@g210573", 80, &toggleMotionDetection, toggleMusic);

void setup()
{
    Serial.begin(115200);
    webServer.begin(); // Initialize the web server
}

void loop()
{
    webServer.handleClient(); // Handle web server clients

    if (motionSensor.isMotionDetected() && motionSensor.getState())
    {
        Serial.println("Motion detected!");
        int drumPattern[] = {NOTE_C2, 0, NOTE_C2, 0, NOTE_C2, 0, NOTE_C2, 0};
        melodyPlayer.playJingle(melody, durations, drumPattern, sizeof(drumPattern) / sizeof(drumPattern[0]), sizeof(melody) / sizeof(melody[0]));
    }
}