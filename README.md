# IoT Home Automation & Safety Interlock System

An integrated Internet of Things (IoT) home automation and life-safety platform built with the **NodeMCU ESP8266 (ESP-12E)** and **Arduino IoT Cloud**. The system provides bidirectional remote switching for four appliances alongside an autonomous hazard detection loop that monitors ambient gas levels, actuates a physical safety valve via servo motor, isolates all relay loads, and triggers local alarms.

Developed as part of a 7th-semester engineering internship curriculum covering embedded firmware development, cloud telemetry, and PCB prototyping.

---

## Key Features

* **Multi-Channel Cloud Switching:** Independent, bidirectional web and mobile dashboard control for four discrete electrical loads via `CloudSwitch` variables.
* **Autonomous Gas Hazard Interlock:** Real-time analog gas sensing via pin `A0`. When readings cross the defined hazard threshold (`sensorValue > 75`):
  * Instantly turns off all four appliance relays to eliminate potential spark/ignition hazards.
  * Forces active cloud switch states to `false`.
  * Drives a mechanical safety servo from `0°` to `180°` (emergency valve shutoff / ventilation hatch).
  * Pulls the hardware safety alarm pin (`Safty`, GPIO 10) `LOW`.
* **Connection Diagnostics:** Visual network feedback via an onboard LED on pin `wifiLed` (GPIO 16), indicating active Wi-Fi and cloud synchronization status.
* **Single-PCB Consolidation:** Eliminates loose breadboard wiring by mounting sensors, relay drivers, power rails, and the NodeMCU module on a unified hardware layout.

---

## Hardware Pinout Specification

**Target Controller:** NodeMCU 1.0 (ESP-12E Module)

| Peripheral | Board Label | ESP8266 Pin | Pin Mode | Logic / Default State |
| :--- | :--- | :--- | :--- | :--- |
| **Relay Channel 1** | `D1` | GPIO 13 | `OUTPUT` | Active LOW |
| **Relay Channel 2** | `D2` | GPIO 4 | `OUTPUT` | Active LOW |
| **Relay Channel 3** | `D5` | GPIO 14 | `OUTPUT` | Active LOW |
| **Relay Channel 4** | `D6` | GPIO 12 | `OUTPUT` | Active LOW |
| **Safety Shutoff Servo** | `D8` | GPIO 15 | `OUTPUT` | `0°` (Normal) / `180°` (Emergency) |
| **Analog Gas Sensor** | `A0` | ADC0 | `INPUT` | Threshold Trip at `> 75` |
| **Safety Alert Output** | `SD3` | GPIO 10 | `OUTPUT` | `HIGH` (Normal) / `LOW` (Triggered) |
| **Wi-Fi Status Indicator** | `D0` | GPIO 16 | `OUTPUT` | `LOW` (Connected) / `HIGH` (Disconnected) |

---

## Internship Curriculum & Milestone Progression

This project served as the final capstone following progressive hands-on laboratory modules:

| Module | Description |
| :--- | :--- |
| **Task 1** | Arduino IoT Cloud initial environment configuration and device pairing. |
| **Task 2** | Remote discrete LED control via cloud dashboard switches. |
| **Task 3** | Color-state reporting and PWM control using RGB LEDs. |
| **Task 4** | Real-time ultrasonic distance acquisition and telemetry streaming. |
| **Hardware Core** | Schematic review, PCB routing fundamentals, and hands-on soldering. |
| **Mini Project** | Integrated 4-channel home automation and emergency gas safety interlock. |

---

## Cloud Variable Architecture

Cloud synchronization is managed via `thingProperties.h` and refreshed through `ArduinoCloud.update()` inside the main super-loop:

```cpp
CloudSwitch switch_1;  // Bidirectional trigger: onSwitch1Change()
CloudSwitch switch_2;  // Bidirectional trigger: onSwitch2Change()
CloudSwitch switch_3;  // Bidirectional trigger: onSwitch3Change()
CloudSwitch switch_4;  // Bidirectional trigger: onSwitch4Change()
int gAS;               // Analog sensor telemetry: onGASChange()
