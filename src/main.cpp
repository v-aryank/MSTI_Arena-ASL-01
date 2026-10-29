#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "soc/soc.h"
#include "soc/gpio_reg.h"

#define SENSOR_PIN 34
#define STATUS_LED 2

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

const unsigned long TELEMETRY_INTERVAL = 3000;

unsigned long lastTelemetryTime = 0;
unsigned long lastPrintTime = 0;

int sensorValue = 0;

void setup() {
  Serial.begin(115200);

  pinMode(SENSOR_PIN, INPUT);
  pinMode(STATUS_LED, OUTPUT);

  analogReadResolution(12);

  // Ensure LED starts OFF using GPIO registers
  REG_WRITE(GPIO_OUT_W1TC_REG, (1U << STATUS_LED));

  Serial.println("\nASL Challenge 01");
  Serial.println("IoT Telemetry Node");
  Serial.println("--------------------------------");

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(250);
  }

  Serial.println("\nWi-Fi connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("--------------------------------");

  lastTelemetryTime = millis();
}

// Send the latest sensor reading to the server
void sendTelemetry(int value) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi disconnected!");
    return;
  }

  HTTPClient http;

  String url = "http://httpbin.org/get?sensor=" + String(value);

  http.setConnectTimeout(1000);
  http.setTimeout(1000);

  Serial.print("Sending telemetry: ");
  Serial.println(value);

  if (http.begin(url)) {
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.print("HTTP Status: ");
      Serial.println(httpCode);
    } else {
      Serial.print("HTTP request failed: ");
      Serial.println(http.errorToString(httpCode));
    }

    http.end();
  } else {
    Serial.println("Unable to initialize HTTP connection.");
  }

  Serial.println("--------------------------------");
}

void loop() {
  // Read the sensor continuously
  sensorValue = analogRead(SENSOR_PIN);

  // Print readings every 200 ms
  unsigned long currentTime = millis();

  if (currentTime - lastPrintTime >= 200) {
    lastPrintTime = currentTime;

    Serial.print("Sensor ADC: ");
    Serial.println(sensorValue);
  }

  // Toggle LED using hardware GPIO registers
  REG_WRITE(GPIO_OUT_W1TS_REG, (1U << STATUS_LED));
  delay(50);

  REG_WRITE(GPIO_OUT_W1TC_REG, (1U << STATUS_LED));
  delay(50);

  // Send telemetry every 3 seconds
  currentTime = millis();

  if (currentTime - lastTelemetryTime >= TELEMETRY_INTERVAL) {
    lastTelemetryTime = currentTime;
    sendTelemetry(sensorValue);
  }
}