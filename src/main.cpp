// #include <Arduino.h>
// #include <microDS18B20.h>
// #include "mario.h"

// int buzzer = 32;  // the pin that the buzzer is attached to
// int buzzer2 = 33; // the second buzzer
// int sensor = 26;  // the pin that the sensor is attached to
// int state = LOW;  // by default, no motion detected
// int val = 0;      // variable to store the sensor status (value)

// void setup()
// {
//   pinMode(buzzer, OUTPUT); // initialize buzzer as an output
//   pinMode(sensor, INPUT);  // initialize sensor as an input
//   Serial.begin(115200);    // initialize serial
// }

// void playJingle(int melody[], int durations[], int drumPattern[], int drumLength, int melodyLength);

// void loop()
// {
//   val = digitalRead(sensor); // read sensor value
//   delay(1000);
//   if (val == HIGH)
//   { // check if the sensor is HIGH
//     if (state == LOW)
//     {
//       Serial.println("Motion detected!");
//       // Simple drum beat
//       int drumPattern[] = {NOTE_C2, 0, NOTE_C2, 0, NOTE_C2, 0, NOTE_C2, 0};
//       playJingle(melody, durations, drumPattern, sizeof(drumPattern) / sizeof(drumPattern[0]), sizeof(melody) / sizeof(melody[0]));
//       state = HIGH; // update variable state to HIGH
//     }
//   }
//   else
//   {
//     if (state == HIGH)
//     {
//       Serial.println("Motion stopped!");
//       state = LOW; // update variable state to LOW
//     }
//   }
// }

// void playJingle(int melody[], int durations[], int drumPattern[], int drumLength, int melodyLength)
// {
//   for (int thisNote = 0; thisNote < melodyLength; thisNote++)
//   {
//     int noteDuration = 1000 / durations[thisNote];
//     tone(buzzer2, melody[thisNote], noteDuration);

//     // Play drum sound on the second buzzer
//     if (thisNote < drumLength)
//     {
//       if (drumPattern[thisNote] != 0)
//       {
//         tone(buzzer, drumPattern[thisNote], noteDuration);
//       }
//     }

//     delay(noteDuration * 1.30);
//     noTone(buzzer);  // stop the tone playing
//     noTone(buzzer2); // stop the drum tone
//   }
// }



// String network_ssid = "Formation";
//     String network_password = "Et@@g210573";


// WORKING
// #include "server.h"

// const char* ssid = "Formation";
// const char* password = "Et@@g210573";

// server_web webServer(ssid, password, 443);

// void setup() {
//     Serial.begin(115200);
//     webServer.begin(); // Initialize the web server
// }

// void loop() {
//     webServer.handleClient(); // Handle web server clients
// }

#include "Sensor.h"
#include "Buzzer.h"
#include "Melody.h"
#include "Server.h"
#include "mario.h"

//FIXME: PLEASE FOR FUCK SAKE ENZO
void toggleMotionDetection() {
    motionSensor.toggleState();
}

Sensor motionSensor(26);
Buzzer buzzer(32), buzzer2(33);
Melody melodyPlayer(buzzer2, buzzer);
server_web webServer("Formation", "Et@@g210573", 80, toggleMotionDetection());



void setup() {
    Serial.begin(115200);
    webServer.begin(); // Initialize the web server
}

void loop() {
    webServer.handleClient(); // Handle web server clients

    if (motionSensor.isMotionDetected() && motionSensor.getState()) {
        Serial.println("Motion detected!");
        int drumPattern[] = {NOTE_C2, 0, NOTE_C2, 0, NOTE_C2, 0, NOTE_C2, 0};
        melodyPlayer.playJingle(melody, durations, drumPattern, sizeof(drumPattern) / sizeof(drumPattern[0]), sizeof(melody) / sizeof(melody[0]));
    }
}