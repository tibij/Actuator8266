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
    setupOneWireBus(12);
}

void loop() {    

    String temperatura;
    currentMillis = millis();  //get the current time
    
    checkMQTT(); // Check connection to the brocker
    
    if (currentMillis - startMillis >= period)  //test whether the period has elapsed
    {
        // Calculam media temperaturilor citite
        if (contor < 20){
            Serial.print("Citeste temperatura ... :");
            
            // Temperatura camera birou
            temperatura = getTemperature(0);
            Serial.print("Temperatura birou: ");
            Serial.println(temperatura);
            
            sum += readTemperature;
            contor++;
            
            Serial.print("Contor: ");
            Serial.println(contor);
        }
        else{
            readTemperature = sum / 20;
            contor = 0;
            sum = 0;
            Serial.print("Temperatura medie:");
            Serial.println(readTemperature);
            
            // Convert temperature to a string with two digits before the comma and 2 digits for precision
            char convertedTemperature[6];
            dtostrf(readTemperature, 2, 2, convertedTemperature);
            temperatura = (String)convertedTemperature;
            publishMQTT(mqttTopicTempBirou, temperatura);        
        }    
        startMillis = currentMillis;
    }    
}