// HC-SR04 -> LED blink-rate demo
// Wiring: Trig -> D9, Echo -> D10, LED (+resistor) -> D6

const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 6;

const float standbyThreshold = 100.0; // cm - beyond this, LED stays solid ON
const float minDistance = 5.0;        // cm - closest realistic reading
const int slowestBlink = 500;         // ms half-period when just inside range
const int fastestBlink = 40;          // ms half-period when very close

unsigned long lastToggleTime = 0;
bool ledState = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float distanceCm = readDistanceCm();

  if (distanceCm <= 0 || distanceCm > standbyThreshold) {
    // Nothing in range -> standby mode, LED solid on
    digitalWrite(ledPin, HIGH);
    Serial.println("Standby (no object in range)");
  } else {
    // Something in range -> blink, faster as distance shrinks
    int blinkInterval = mapDistanceToBlinkInterval(distanceCm);

    unsigned long now = millis();
    if (now - lastToggleTime >= (unsigned long)blinkInterval) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState ? HIGH : LOW);
      lastToggleTime = now;
    }

    Serial.print("Distance: ");
    Serial.print(distanceCm);
    Serial.print(" cm | Blink interval: ");
    Serial.print(blinkInterval);
    Serial.println(" ms");
  }
}

float readDistanceCm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  if (duration == 0) return -1; // no echo = out of range

  return duration * 0.0343 / 2;
}

int mapDistanceToBlinkInterval(float distanceCm) {
  distanceCm = constrain(distanceCm, minDistance, standbyThreshold);
  return map(distanceCm, minDistance, standbyThreshold, fastestBlink, slowestBlink);
}
