# Test Results

## Test Environment
- Simulator: Wokwi
- Board: ESP32 DevKit
- Sensor: Potentiometer
- ADC pin: GPIO34
- Protocol: HTTP GET

## Test Cases

| Test | Expected Result | Result |
|---|---|---|
| Startup | Startup message appears | Pending |
| Wi-Fi | ESP32 connects successfully | Previously observed in simulation |
| ADC minimum | Reading approaches 0 | Previously observed in simulation |
| ADC maximum | Reading approaches 4095 | Previously observed in simulation |
| HTTP telemetry | HTTP 200 response | Previously observed in simulation |
| LED operation | LED toggles | Verify visually |
| Wi-Fi interruption | Failure is handled | Pending |

## Evidence
Save genuine screenshots and serial logs in evidence/simulation/.
Save physical prototype test evidence in evidence/hardware/.

Only mark a test as passed after verifying the result.
