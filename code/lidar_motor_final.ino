// TF-Luna LiDAR -> Vibration Motor (pulsing haptic feedback)
// Wiring (Arduino Nano):
//   TF-Luna Pin 1 (5V)      -> Nano 5V
//   TF-Luna Pin 2 (SDA)     -> Nano A4
//   TF-Luna Pin 3 (SCL)     -> Nano A5
//   TF-Luna Pin 4 (GND)     -> Nano GND
//   TF-Luna Pin 5 (GND/I2C) -> Nano GND (enables I2C mode)
//   Motor -> D6 (through transistor circuit)
//
// Requires the "TFLI2C" library (by Bud Ryerson) - install via Library Manager

#include <Wire.h>
#include "TFLI2C.h"

TFLI2C tflI2C;
int16_t tfDist;
int16_t tfAddr = TFL_DEF_ADR; // default I2C address 0x10

const int motorPin = 6;

const float standbyThreshold = 120.0; // cm - beyond this, motor is OFF
const float minDistance = 20.0;       // cm - TF-Luna's practical close range

const int slowestPulseInterval = 600; // ms between pulses when just entering range
const int fastestPulseInterval = 80;  // ms between pulses when very close

const int weakestVibration = 120;     // PWM value for far pulses (above motor's dead zone)
const int strongestVibration = 255;   // PWM value for close pulses

unsigned long lastPulseTime = 0;
bool motorOn = false;

void setup() {
  pinMode(motorPin, OUTPUT);
  analogWrite(motorPin, 0);

  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  float distanceCm = readDistanceCm();

  if (distanceCm <= 0 || distanceCm > standbyThreshold) {
    analogWrite(motorPin, 0);
    motorOn = false;
    Serial.println("No object detected - motor off");
    return;
  }

  distanceCm = constrain(distanceCm, minDistance, standbyThreshold);

  int currentPulseInterval = map(distanceCm, minDistance, standbyThreshold,
                                  fastestPulseInterval, slowestPulseInterval);
  int vibrationStrength = map(distanceCm, minDistance, standbyThreshold,
                               strongestVibration, weakestVibration);

  unsigned long now = millis();
  unsigned long pulseOnDuration = currentPulseInterval / 3;

  if (!motorOn && (now - lastPulseTime >= (unsigned long)currentPulseInterval)) {
    analogWrite(motorPin, vibrationStrength);
    motorOn = true;
    lastPulseTime = now;
  } else if (motorOn && (now - lastPulseTime >= pulseOnDuration)) {
    analogWrite(motorPin, 0);
    motorOn = false;
  }

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.print(" cm | Interval: ");
  Serial.print(currentPulseInterval);
  Serial.print(" ms | Strength: ");
  Serial.println(vibrationStrength);
}

float readDistanceCm() {
  if (tflI2C.getData(tfDist, tfAddr)) {
    return (float)tfDist;
  }
  return -1;
}
