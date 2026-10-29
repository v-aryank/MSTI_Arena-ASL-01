# ASL Challenge 01 — IoT Telemetry Node

An ESP32-based IoT telemetry node developed for the ALPHA SCIENCE LAB (ASL) National Arena challenge.

## Overview

The system reads a potentiometer's analog value, displays the readings through the Serial Monitor, connects to Wi-Fi, and transmits sensor data to an HTTP endpoint every three seconds.

## Features

- ESP32 DevKit V1
- 12-bit analog sensor reading (0–4095)
- Wi-Fi connectivity using `Wokwi-GUEST`
- HTTP GET telemetry transmission
- Telemetry interval of approximately 3 seconds
- Status LED controlled through ESP32 GPIO hardware registers
- Serial Monitor output for sensor readings and HTTP status

## Wokwi Simulation

**Project URL:** https://wokwi.com/projects/479247402232513537


## Hardware and Wiring

| Component | ESP32 Pin |
|---|---|
| Potentiometer SIG | GPIO 34 |
| Status LED | GPIO 2 |
| Wi-Fi | Wokwi-GUEST |

Connect the potentiometer's power and ground pins to the appropriate supply and ground connections in the Wokwi circuit.

## Sensor Pin Selection

GPIO 34 is used for analog sensor input in the current implementation.

On the classic ESP32, GPIO 4 and GPIO 15 are ADC2 pins. ADC2 shares hardware resources with Wi-Fi, which can prevent reliable ADC2 readings while Wi-Fi is active. GPIO 34 belongs to ADC1 and is suitable for analog readings while Wi-Fi is operating.

For this reason, GPIO 34 was selected to maintain reliable sensor readings during Wi-Fi telemetry.

**Note:** The challenge specifies GPIO 4 or GPIO 15. GPIO 34 is a documented implementation deviation and may require organizer approval.

## Telemetry

The ESP32 sends HTTP GET requests to the test endpoint:

`http://httpbin.org/get?sensor=<ADC_VALUE>`

A successful HTTP response, such as status `200`, indicates that the request reached the endpoint successfully. This endpoint is for testing and does not provide permanent telemetry storage.

## Status LED

The status LED on GPIO 2 is controlled using:

- `GPIO_OUT_W1TS_REG` — set the GPIO output.
- `GPIO_OUT_W1TC_REG` — clear the GPIO output.

The status LED is not controlled using `digitalWrite()`.

## Test Results

- Wi-Fi connection: Successful
- Sensor readings: Responsive to potentiometer changes
- HTTP GET requests: Successful, HTTP status 200
- ADC range observed: 0–4095
- Simulation environment: Wokwi

## Wokwi Simulation

**Project URL:** Add your public Wokwi project link here.

## Files

- `sketch.ino` — ESP32 firmware
- `diagram.json` — circuit configuration
- `libraries.txt` — external library list, if required
- `wokwi.toml` — Wokwi project configuration, if required

## Challenge

ALPHA SCIENCE LAB (ASL) National Arena — Challenge 01: Build an IoT Telemetry Node