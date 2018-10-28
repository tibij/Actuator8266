#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "main.h"

void setup() {
    // setup serial port
    Serial.begin(115200);

    // setup device pins
    setupGPIOs();
    
    // setup WiFi
    setupWiFi();

    // setup MQTT connection
    setupMQTT();

    // setup OneWire bus for reading temperature
    // setupOneWireBus();
}

void loop() {    
    Serial.println("Fac ce fac si stau degeaba ...");
    checkMQTT();
    delay(5000);
}