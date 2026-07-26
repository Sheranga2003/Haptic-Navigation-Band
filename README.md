# Haptic-Navigation-Band
A wearable device that uses distance sensing to give haptic (vibration) feedback about nearby obstacles — built as a low-cost assistive navigation aid concept for visually impaired users.

## 🎥 Demo
*(Coming soon — build in progress)*

## 💡 The Problem
Traditional canes only detect obstacles at ground level and require physical contact. This project explores whether distance-based haptic feedback — closer object = stronger/faster vibration — can give a wearer a sense of their surroundings without sound or contact.

## 🛠️ How It Works
1. A distance sensor continuously scans for nearby objects
2. Distance readings are mapped to vibration intensity/frequency
3. The wearer feels stronger, faster vibration as they approach an obstacle — no vibration means no obstacle in range

## 📦 Hardware
| Component | Purpose |
|---|---|
| Arduino Uno | Microcontroller |
| HC-SR04 (prototype) → VL53L1X LiDAR (final) | Distance sensing |
| ERM coin vibration motor (10mm, 3V) | Haptic feedback |
| 2N2222 transistor + 1N4001 diode | Motor driver circuit |
| 3D printed enclosure (Fusion 360) | Wearable housing |

## 🔌 Circuit Diagram
*(insert the SVG diagrams here)*

## 💻 Code
See [`/code`](./code) for Arduino sketches:
- `ultrasonic_led_test.ino` — early prototype, LED stands in for motor
- `ultrasonic_motor.ino` — vibration motor version
- `lidar_motor_final.ino` — final LiDAR-based version

## 📈 Development Log
- **[Date]** — Prototyped distance-to-blink-rate logic with HC-SR04 + LED on breadboard
- **[Date]** — Swapped LED for vibration motor, added transistor driver circuit
- **[Date]** — Switched sensor to VL53L1X LiDAR for better accuracy/range
- **[Date]** — Designed and printed wearable enclosure in Fusion 360

## 🧠 Challenges & Decisions
- *Why ERM over LRA motor:* simpler PWM control, no dedicated driver chip needed
- *Why LiDAR over ultrasonic:* narrower beam = more precise directional feedback, smaller footprint for wearable design
- *(add more as you hit real snags — this section matters most to reviewers)*

## 🚀 Future Improvements
- Multiple sensors for directional feedback (left/right/front)
- Bluetooth logging via ESP32 for a companion app
- Battery-powered standalone wearable version

## 📷 Build Photos
*(breadboard → enclosure → final assembly, in order)*
