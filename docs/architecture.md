# System Architecture

## Overview
An ESP32 reads an analog input, connects to Wi-Fi, and sends sensor
readings through HTTP GET requests.

## Components
- ESP32 DevKit
- Potentiometer as an analog sensor simulator
- Status LED
- 220-ohm resistor
- Wi-Fi network
- HTTP test endpoint

## Pin Configuration
- Sensor signal: GPIO34
- Status LED: GPIO2
- Potentiometer VCC: 3.3V
- Potentiometer GND: ESP32 GND

## Signal Flow
Potentiometer -> GPIO34 ADC -> ESP32 -> Wi-Fi -> HTTP GET endpoint

ESP32 GPIO2 -> LED -> 220-ohm resistor -> GND

## ADC Pin Selection
GPIO34 is an ADC1 input pin on the classic ESP32. GPIO4 and GPIO15
are ADC2 pins, which can conflict with Wi-Fi operation.

GPIO34 differs from the challenge's specified GPIO4 or GPIO15.
This deviation should be disclosed to the organizers if strict
pin compliance is required.

## Telemetry
The firmware attempts an HTTP GET request approximately every
three seconds. Requests are synchronous and may temporarily pause
sensor sampling.

## Limitations
- The potentiometer simulates an analog sensor.
- The HTTP endpoint is for testing, not a production backend.
- Simulation does not replace physical hardware validation.
