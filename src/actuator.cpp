#include <Arduino.h>
#include "actuator.h"

void publishMQTT(const char* mqttTopic, String value);

// Parametri de stare pompa
int starePompaPardoseala = 0;
int starePompa = 0;

void setupGPIOs(){
    // Set pin mode
    pinMode(releuPompa, OUTPUT);

    // Setam starea initiala a pompei ca oprit (HIGH = OPRIT)
    digitalWrite(releuPompa, HIGH);
    analogRead(A0);
}

void controlPompa(String stareDorita){
    int output;
    // Daca pompa de pardoseala din beci e oprita atunci oprim si pompa de la etaj
    if (stareDorita == "0")
        digitalWrite(releuPompa, LOW);
    // Daca pompa de pardoseala din beci e pornita atunci pornim si pompa de la etaj
    if (stareDorita == "1")
        digitalWrite(releuPompa, HIGH);
    // Publicam starea pompei
    publishMQTT(mqttTopicPompaEtaj, stareDorita);
}

