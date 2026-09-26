# IoT Home Automation & Safety Interlock System

An integrated Internet of Things (IoT) home automation and life-safety platform built with the **NodeMCU ESP8266 (ESP-12E)** and **Arduino IoT Cloud**[cite: 10, 12, 13, 14]. The system provides bidirectional remote switching for four appliances alongside an autonomous hazard detection loop that monitors ambient gas levels, actuates a physical safety valve via servo motor, isolates all relay loads, and triggers local alarms[cite: 10, 13, 14].

Developed as part of a 7th-semester engineering internship curriculum covering embedded firmware development, cloud telemetry, and PCB prototyping[cite: 8, 10].

---

## Key Features

* **Multi-Channel Cloud Switching:** Independent, bidirectional web and mobile dashboard control for four discrete electrical loads via `CloudSwitch` variables[cite: 10, 13, 14].
* **Autonomous Gas Hazard Interlock:** Real-time analog gas sensing via pin `A0`[cite: 10, 14]. When readings cross the defined hazard threshold (`sensorValue > 75`)[cite: 10, 14]:
  * Instantly turns off all four appliance relays to eliminate potential spark/ignition hazards[cite: 10, 14].
  * Forces active cloud switch states to `false`[cite: 10, 14].
  * Drives a mechanical safety servo from `0°` to `180°` (emergency valve shutoff / ventilation hatch)[cite: 10, 14].
  * Pulls the hardware safety alarm pin (`Safty`, GPIO 10) `LOW`[cite: 10, 14].
* **Connection Diagnostics:** Visual network feedback via an onboard LED on pin `wifiLed` (GPIO 16), indicating active Wi-Fi and cloud synchronization status[cite: 10, 14].
* **Single-PCB Consolidation:** Eliminates loose breadboard wiring by mounting sensors, relay drivers, power rails, and the NodeMCU module on a unified hardware layout[cite: 8, 11].

---

## Hardware Pinout Specification

**Target Controller:** NodeMCU 1.0 (ESP-12E Module)

| Peripheral | Board Label | ESP8266 Pin | Pin Mode | Logic / Default State |
| :--- | :--- | :--- | :--- | :--- |
| **Relay Channel 1**[cite: 10, 14] | `D1` | GPIO 13[cite: 10] | `OUTPUT`[cite: 10] | Active LOW[cite: 10] |
| **Relay Channel 2**[cite: 10, 14] | `D2`[cite: 10] | GPIO 4[cite: 10] | `OUTPUT`[cite: 10] | Active LOW[cite: 10] |
| **Relay Channel 3**[cite: 10, 14] | `D5`[cite: 10] | GPIO 14[cite: 10] | `OUTPUT`[cite: 10] | Active LOW[cite: 10] |
| **Relay Channel 4**[cite: 10, 14] | `D6`[cite: 10] | GPIO 12[cite: 10] | `OUTPUT`[cite: 10] | Active LOW[cite: 10] |
| **Safety Shutoff Servo**[cite: 10, 14] | `D8`[cite: 14] | GPIO 15[cite: 10, 14] | `OUTPUT`[cite: 10] | `0°` (Normal) / `180°` (Emergency)[cite: 10, 14] |
| **Analog Gas Sensor**[cite: 10, 14] | `A0`[cite: 10] | ADC0[cite: 14] | `INPUT`[cite: 10] | Threshold Trip at `> 75`[cite: 10, 14] |
| **Safety Alert Output**[cite: 10, 14] | `SD3`[cite: 10] | GPIO 10[cite: 10] | `OUTPUT`[cite: 10] | `HIGH` (Normal) / `LOW` (Triggered)[cite: 10, 14] |
| **Wi-Fi Status Indicator**[cite: 10, 14] | `D0`[cite: 10] | GPIO 16[cite: 10] | `OUTPUT`[cite: 10] | `LOW` (Connected) / `HIGH` (Disconnected)[cite: 10, 14] |

---

## Internship Curriculum & Milestone Progression

This project served as the final capstone following progressive hands-on laboratory modules[cite: 8, 10]:

| Module | Description |
| :--- | :--- |
| **Task 1** | Arduino IoT Cloud initial environment configuration and device pairing[cite: 8]. |
| **Task 2** | Remote discrete LED control via cloud dashboard switches[cite: 8]. |
| **Task 3** | Color-state reporting and PWM control using RGB LEDs[cite: 8]. |
| **Task 4** | Real-time ultrasonic distance acquisition and telemetry streaming[cite: 8]. |
| **Hardware Core** | Schematic review, PCB routing fundamentals, and hands-on soldering[cite: 8, 11]. |
| **Mini Project** | Integrated 4-channel home automation and emergency gas safety interlock[cite: 8, 10]. |

---

## Cloud Variable Architecture

Cloud synchronization is managed via `thingProperties.h` and refreshed through `ArduinoCloud.update()` inside the main super-loop[cite: 10, 13]:

```cpp
CloudSwitch switch_1;  // Bidirectional trigger: onSwitch1Change()
CloudSwitch switch_2;  // Bidirectional trigger: onSwitch2Change()[cite: 13]
CloudSwitch switch_3;  // Bidirectional trigger: onSwitch3Change()[cite: 13]
CloudSwitch switch_4;  // Bidirectional trigger: onSwitch4Change()[cite: 13]
int gAS;               // Analog sensor telemetry: onGASChange()[cite: 10, 13]
