# ESP32 Documentation and Our Projects

## Objective 1: Light an LED

In this section, we will demonstrate how to illuminate an LED using the ESP32 and set up the necessary equipment.

### Introduction to ESP32

The ESP32 is an extremely versatile microcontroller with Wi-Fi and Bluetooth capabilities. It boasts numerous GPIO pins that can be harnessed for a wide range of projects. Below is an image illustrating the GPIO pins (please note that the layout may vary depending on the version):

![GPIO Pinout](GPIOS.webp)

### Step 1: ESP32 Configuration

Before turning on a LED, it's essential to ensure that your ESP32 is correctly configured. Confirm that your development environment is set up accurately and that your ESP32 is properly connected.

### Step 2: LED Connection

Connect an LED to one of the GPIO pins on the ESP32. Remember to incorporate an appropriate resistor to safeguard the LED from overloading. It's crucial to adhere to the specifications of your LED and the recommendations for your ESP32.

### Step 3: Writing the Code

To control the LED, you'll need to create a program. Below is a straightforward example using the Arduino programming language:

```arduino
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
```

This code causes the ESP32's built-in LED to blink at one-second intervals.

### Step 4: Uploading the Code

Upload your code to the ESP32 through your chosen development environment, such as PlatformIO in VSCode.

### Step 5: Observing the Outcome

Once the code is uploaded, you should observe the LED blinking at regular intervals.

## Objectif 2: light a led thanks to a sensor

In this section, we will demonstrate how to illuminate an LED with a sensor and using the ESP32.

### step 1: repeat the same five step

We need to repeat the same five step as in the firs part and add the sensor in the circuit.

### step 2: add the sensor

To aad the sensor we need to connect his three pin to the circuit:
first one is the ground
secound one is the out
last one is the VCC 5-12 VDC

like in the photo below:

![ledAndSensor circuit](ledAndSensor.JPG)

Luckly the resistance was the good one and this is the calcul to check that :

    U = R . I
<=> R = U / I

<=> R = 3,3 / 1.10^-3

<=> R = 3,3KOhm

## Objectif 3: generate music with a sensor

In this section, we will demonstrate how to turn on a buzzer with a sensor and using the ESP32.

### step 1: keep the same circuit but switch the led with the buzzer

there is the photo of the circuit:

![buzzerAndSensor circuit](buzzerAndSensor.JPG)

### step 2: define some note and make a real music

To make a real music we need to define the notes before to use theme: 

these notes are frequencies that we have defined in int :

Exemple :
```cpp
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
```


