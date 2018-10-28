#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "mqtt.h"

void subscribeMQTT(const char* mqttTopic);
int setupWiFi();
void controlPompa(String stareDorita);

WiFiClient mqttWiFiClient;
PubSubClient mqttClient(mqttWiFiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String value;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    value += (char)payload[i];
  }
  Serial.println();
  
  // Seteaza pompa
  controlPompa(value);
}

int reconnect() {

  // Check if WiFi connection is still up and if not try to reconnect
  int wifiStatus = WiFi.status();
  if (wifiStatus != WL_CONNECTED) {
    Serial.print("Attempting to reconnect to WiFi...");
    wifiStatus = setupWiFi();
  }

  // Loop until we're reconnected but stop after 3 attempts or no Internet connection 
  int retryCount = 0;
  while (!mqttClient.connected() && (retryCount < 3) && (wifiStatus == WL_CONNECTED) )  {
    Serial.println("Attempting MQTT connection...");
    
    // Attempt to connect
    if (mqttClient.connect("ActuatorESP8266")) {
      Serial.println("Connected to MQTT broker");
      subscribeMQTT(mqttTopicPompaPardoseala);
    } else {
      Serial.print("Failed to connect to MQTT broker, return code = ");
      Serial.print(mqttClient.state());
      Serial.println(" will try again in 3 seconds");

      // Wait 3 seconds before retrying
      delay(3000);
    }
    retryCount++;
  }
  return mqttClient.connected();
}

int checkMQTT() {
  int isConnected = mqttClient.connected();
  Serial.print("MQTTConnected status: ");
  Serial.println(isConnected);
    if (!isConnected)
        isConnected = reconnect();
    else
        mqttClient.loop();
  return isConnected;
}

void setupMQTT() {
  
  Serial.println("Setup MQTT connections");
  mqttClient.setServer(mqttServer, 1883);
  mqttClient.setCallback(callback);

  // Estabilish initial connection
  checkMQTT();
}

void publishMQTT(const char* mqttTopic, String value) {
    
    int result;
    char valueString[20];

    // Publish only if connection is fine to MQTT broker
    if ( mqttClient.connected() ) {
        
        mqttClient.loop();
              
        value.toCharArray(valueString,20);
        
        Serial.print("Topic: ");
        Serial.print(mqttTopic);
        Serial.print(" ");
        Serial.print(value);
        
        result = mqttClient.publish(mqttTopic, valueString, 1);
        
        if (result)
          Serial.println(" Publish: SUCCESS");
        else
          Serial.println(" Publish: FAILED ");
    }
}

void subscribeMQTT(const char* mqttTopic) {
    
    int result;
    char valueString[20];
    
    Serial.println("Subscribing ...");

    // Subscribe only if connection is fine to MQTT broker
    if ( mqttClient.connected() ) {
        
        mqttClient.loop();
        
        Serial.print("Subscribe to topic: ");
        Serial.print(mqttTopic);
        
        result = mqttClient.subscribe(mqttTopic);
        
        if (result)
          Serial.println(" Subscribe: SUCCESS");
        else
          Serial.println(" Subscribe: FAILED ");
    }
    else
        Serial.println("Could not subscribe. Not connected to MQTT broker.");
}
