# Failure Analysis

## 1. Wi-Fi Connection Failure
Potential causes:
- Network unavailable
- Incorrect network configuration
- Connection timeout

Current behavior:
The firmware waits for Wi-Fi during startup. If the connection
never succeeds, normal startup does not continue.

## 2. HTTP Request Failure
Potential causes:
- Network interruption
- Endpoint unavailable
- Connection timeout
- Server error

Current behavior:
The firmware reports HTTP request errors in the serial monitor.

## 3. ADC Reading Problems
Potential causes:
- Incorrect wiring
- Incorrect pin selection
- Sensor power or ground issue

Mitigation:
Check wiring and use an ADC1 pin when Wi-Fi is active on the
classic ESP32.

## 4. Validation
Test each failure scenario and record the observed result.
Do not claim recovery behavior until it has been verified.
