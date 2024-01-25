/**
 * @file sensor.h
 * @brief Contains the definition of the Sensor class for motion detection.
 *
 * This file declares the Sensor class, which is used for detecting motion through a digital sensor
 * connected to an ESP32 or similar microcontroller.
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <microDS18B20.h>

/**
 * @class Sensor
 * @brief Manages a motion sensor.
 *
 * This class encapsulates the functionality of a motion sensor. It provides methods to check
 * if motion is detected and to control the operational state of the sensor.
 */
class Sensor
{
public:
    /**
     * @brief Constructs a Sensor object.
     *
     * @param pin The microcontroller pin to which the sensor is connected.
     */
    Sensor(int pin) : sensorPin(pin)
    {
        pinMode(sensorPin, INPUT);
        state = true;
    }

    /**
     * @brief Checks if motion is detected by the sensor.
     *
     * @return true if motion is detected, false otherwise.
     */
    bool isMotionDetected()
    {
        return digitalRead(sensorPin) == HIGH;
    }

    /**
     * @brief Activates the sensor to detect motion.
     */
    void turnOn()
    {
        state = true;
    }

    /**
     * @brief Deactivates the sensor to stop detecting motion.
     */
    void turnOff()
    {
        state = false;
    }

    /**
     * @brief Gets the current operational state of the sensor.
     *
     * @return true if the sensor is active, false if it is inactive.
     */
    bool getState()
    {
        return state;
    }

    /**
     * @brief Toggles the operational state of the sensor.
     */
    void toggleState()
    {
        state = !state;
    }

private:
    int sensorPin; ///< The microcontroller pin to which the sensor is connected.
    bool state;    ///< Indicates whether the sensor is active (true) or inactive (false).
};

#endif // SENSOR_H
