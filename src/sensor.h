#include <Arduino.h>
#include <microDS18B20.h>

#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
public:
    Sensor(int pin) : sensorPin(pin) {
        pinMode(sensorPin, INPUT);
    }

    bool isMotionDetected() {
        return digitalRead(sensorPin) == HIGH;
    }

private:
    int sensorPin;
};

#endif // SENSOR_H
