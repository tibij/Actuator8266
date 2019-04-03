#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "main.h"

String temperaturaTur;
float readTemperature;

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
    setupOneWireBus(12);
}

void loop() {    
    
    String temperatura;
    // Check connection to the brocker
    checkMQTT();
    
    // Temperatura camera birou
    temperatura = getTemperature(0);
    Serial.print("Temperatura birou: ");
    Serial.println(temperatura);
    publishMQTT(mqttTopicTempBirou, temperatura);
    
    delay(5000);
}