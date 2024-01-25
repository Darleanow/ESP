#include <Arduino.h>
#include <microDS18B20.h>

#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
public:
    Sensor(int pin) : sensorPin(pin) {
        pinMode(sensorPin, INPUT);
        state = true;
    }

    bool isMotionDetected() {
        return digitalRead(sensorPin) == HIGH;
    }

    void turnOn() {
        state = true;
    }

    void turnOff() {
        state = false;
    }

    bool getState() {
        return state;
    }

    void toggleState() {
        state = !state;
    }

private:
    int sensorPin;
    bool state;
};

#endif // SENSOR_H
