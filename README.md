# Embedded Systems Journey

![Status](https://img.shields.io/badge/status-active-brightgreen)
![Timeline](https://img.shields.io/badge/timeline-6%20months-blue)
![Focus](https://img.shields.io/badge/focus-embedded%20systems-orange)
![Language](https://img.shields.io/badge/language-C-informational)
![Hardware](https://img.shields.io/badge/hardware-Arduino%20%7C%20STM32%20%7C%20ESP32-purple)
![Goal](https://img.shields.io/badge/goal-firmware%20portfolio-success)

A structured journey to learn embedded systems through hands-on labs, C drills, Arduino projects, communication protocols, STM32 bare-metal firmware, FreeRTOS, PCB design, secure OTA updates, and a final capstone project.

This repository is my public lab notebook, project archive, skill tracker, and interview-prep portfolio.

---

## Goal

The goal of this repository is to become strong enough in embedded systems to build, debug, document, and explain real firmware projects.

By the end of this plan, I should be able to:

- Read schematics and build basic circuits
- Use a multimeter and logic analyzer
- Write embedded C with pointers, structs, bitwise operations, and ring buffers
- Build Arduino projects using GPIO, ADC, PWM, timers, UART, I2C, and SPI
- Program STM32 boards at the register level without relying on HAL
- Debug interrupts, DMA, linker files, `.map` files, and hard faults
- Build FreeRTOS projects using tasks, queues, mutexes, and state machines
- Design, order, bring up, and document a custom PCB
- Implement OTA and signed OTA firmware updates
- Publish a final capstone project with a demo video, README, blog post, and resume-ready bullets

---

## Timeline

**Window:** July 6, 2026 – January 3, 2027  
**Pace:** ~15–18 hours per week  
**Main rule:** The unit of progress is a finished, committed, documented build.

If a week slips, I will cut stretch goals first — not checkpoint skills.

---

## Repository Structure

```text
embedded-journey/
├── README.md
├── notes/
│   └── week#.md
├── c-drills/
│   └── week#/
├── 01-electronics-labs/
├── 02-arduino/
├── 03-protocols/
├── 04-stm32-baremetal/
├── 05-rtos/
├── 06-pcb/
└── 07-capstone/