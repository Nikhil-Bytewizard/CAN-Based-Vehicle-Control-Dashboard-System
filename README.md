# 🚘 CAN-Enabled Vehicle Dashboard Control System using LPC2129

## 📌 Project Overview

This project demonstrates a **CAN (Controller Area Network) protocol-based communication system** between two **LPC2129 (ARM7TDMI)** microcontrollers, emulating a **Vehicle Body Control Module (BCM)**. The system allows one ECU to read input from physical switches and transmit the status over the CAN bus to a second ECU, which controls vehicle indicators (LEDs) and displays the state on a **16x2 LCD display**.

It aims to replicate real-time, reliable inter-ECU communication seen in modern automobiles, where different subsystems (like lighting, engine, infotainment, etc.) interact over a common CAN network.

---

## 🎯 Objectives

- Simulate a basic automotive **BCM system** using CAN communication.
- Enable **LED-based control** of vehicle lights (headlights, indicators) based on switch inputs.
- Display the real-time **status of the system on a 16x2 LCD**.
- Implement a scalable and modular codebase for dual-ECU embedded communication.

---

## 🧰 Technologies & Tools Used

| Tool / Component     | Description                                |
|----------------------|--------------------------------------------|
| **LPC2129 MCU**      | ARM7TDMI-S based microcontroller            |
| **CAN Protocol**     | Used for inter-ECU communication            |
| **Keil uVision**     | IDE for ARM programming                     |
| **Flash Magic**      | Flashing tool for LPC series                |
| **Embedded C**       | Programming language                        |
| **16x2 LCD**         | Status display unit (HD44780 compatible)    |
| **LEDs & Switches**  | Represent vehicle lights and inputs         |
| **CAN Transceiver**  | (e.g., MCP2551) to interface CAN bus        |

---

## 🔌 System Architecture

[Switches + LCD] --> ECU 1 (LPC2129) --CAN BUS--> ECU 2 (LPC2129) --> [LEDs]


- **ECU 1 (Control Unit):** Reads switch inputs and sends corresponding CAN messages.
- **ECU 2 (Actuator Unit):** Receives CAN messages, activates LEDs, and sends feedback to LCD.

---

## ⚙️ Functional Description

### ECU 1 – Control & Display Node:
- Monitors input from 3 tactile switches:
  - Left Indicator
  - Right Indicator
  - Headlight
- Sends message frames via CAN based on the switch status.
- Displays system status (active lights) on a **16x2 LCD**.

### ECU 2 – Actuator Node:
- Listens on CAN for control frames.
- Activates/deactivates LEDs representing indicators and headlights.
- Optionally sends back status for LCD display (for future scalability).

---

## 🧩 CAN Frame Format (Custom Design)

| Byte | Purpose             |
|------|---------------------|
| 0    | Command ID (e.g., 0x01 for Indicator) |
| 1    | Sub-command (e.g., 0x10 = Left ON, 0x11 = Left OFF) |
| 2–7  | Reserved for future extension |

---

## 🖥️ Hardware Setup

- **ECU Boards:** Two LPC2129 boards (can be simulated in Proteus).
- **Connections:**
  - CAN_TX/RX → MCP2551 (or SN65HVD230)
  - Switches → GPIO pins
  - LCD → GPIO via 4-bit mode
  - LEDs → GPIO for output control
- **Power Supply:** 5V regulated

---

## 📂 Project Structure

CAN-Vehicle-Dashboard/
 - ECU1_Controller_Code/ # Code for switch & LCD logic
 - ECU2_Actuator_Code/ # Code for LED control
 - Circuit_Diagrams/ # Proteus/Fritzing wiring diagrams
 - README.md # This documentation
 - Docs/ # Additional documents or reports

---

## 🚀 How to Run the Project

1. Open respective codes in **Keil uVision** for ECU 1 and ECU 2.
2. Build and compile the projects.
3. Flash the hex files into LPC2129 boards using **Flash Magic**.
4. Ensure CAN transceivers are properly connected between both ECUs.
5. Power the boards and observe:
   - LCD shows system status
   - LEDs reflect button inputs via CAN

---

## 🧠 Key Learnings

- Practical understanding of **CAN protocol** implementation.
- Experience with **multi-microcontroller communication**.
- Embedded C coding for **real-time hardware control**.
- Use of **LCD and GPIO interfacing** in embedded systems.

---

## 🔮 Future Enhancements

- Add **error frames & acknowledgment** handling.
- Expand to **multi-node CAN network** (3+ ECUs).
- Integrate with **CANoe** for professional simulation and testing.
- Add **UART logging** for debugging and real-time monitoring.
- Implement **interrupt-driven CAN handlers** for better performance.

---
> - Switch input triggering CAN transmission
> - LCD showing active lights
> - LEDs glowing based on input

---

## 📄 License

This project is licensed under the **MIT License** – feel free to use and modify for educational or professional purposes.

---

