# Arduino Snake Game (Nokia Style)

A beginner-friendly Arduino project that recreates the classic Snake game using an 8x8 MAX7219 LED Matrix, controlled by a KY-023 joystick, and enhanced with buzzer sound effects.

This project demonstrates basic game logic, joystick input handling, and LED matrix control in a fun and interactive way.

---

## 📌 Project Overview

This project is inspired by the classic Snake game from old Nokia phones.

The snake moves across an 8x8 grid and is controlled using a joystick. The goal is to eat food, grow longer, and avoid colliding with itself.

To enhance the gameplay experience, sound effects are added:
- Movement beep for feedback  
- Eating sound for reward  
- Game over sound with animation  

This example is designed to be beginner-friendly while still demonstrating real game logic implementation.

---

## 🧰 Components Required

- Arduino Uno / Nano  
- MAX7219 8x8 LED Matrix Module  
- KY-023 Joystick Module  
- Buzzer (Active or Passive)  
- Jumper Wires  
- Breadboard (optional)  

---

## 🔌 Wiring Connections

| Component            | Arduino |
|---------------------|----------|
| MAX7219 VCC         | 5V       |
| MAX7219 GND         | GND      |
| MAX7219 DIN         | D11      |
| MAX7219 CS          | D10      |
| MAX7219 CLK         | D13      |
| Joystick VRx        | A0       |
| Joystick VRy        | A1       |
| Joystick SW         | D2 (not used in this project) |
| Joystick VCC        | 5V       |
| Joystick GND        | GND      |
| Buzzer (+)          | D3       |
| Buzzer (-)          | GND      |

---

## 📷 Wiring Diagram

![Wiring Diagram](diagram.png)

> Make sure your wiring matches the diagram above before uploading the code.

---

## 💻 Arduino Code

You can download the Arduino sketch here:

[Download Arduino Code](Arduino_Snake_Game.ino)

Or open the `.ino` file directly inside this repository.

---

## 🚀 Getting Started

1. Connect all components according to the wiring table.
2. Upload the provided Arduino sketch.
3. Power the Arduino.
4. Use the joystick to control the snake.
5. Eat food and avoid hitting yourself.

---

## 🧠 Learning Concepts

This project helps you understand:

- Basic game logic (Snake mechanics)
- Array usage for object tracking
- LED matrix control (MAX7219)
- Analog input reading (joystick)
- Direction control logic
- Collision detection
- Sound generation using buzzer
- Timing using millis()

---

## 🔄 Possible Improvements

You can expand this project by adding:

- Score display (Serial Monitor or LED scroll)
- Increasing speed levels
- Multiple LED matrices (16x8 or larger)
- Pause / Start button
- Sound effects using DFPlayer Mini
- Game menu system

---

## 🎥 Video Tutorial

Watch the full step-by-step tutorial on YouTube:

👉 (Add your video link here)

In this video, you will see:
- Complete wiring demonstration  
- Code explanation  
- Gameplay demo  
- Sound effects in action  

If this project helps you, consider subscribing for more beginner-friendly Arduino tutorials 🚀

---

## 📄 License

This project is open-source and free to use for educational purposes.

---

Happy Coding 🚀
