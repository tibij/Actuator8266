#include <Arduino.h>
#include "actuator.h"

// Parametri de stare pompa
int starePompaPardoseala = 0;
int starePompa = 0;

void setupGPIOs(){
    // Set pin mode
    pinMode(releuPompa, OUTPUT);

    // Setam starea initiala a pompei ca oprit (HIGH = OPRIT)
    digitalWrite(releuPompa, HIGH);
}

void controlPompa(String stareDorita){
    int output;
    if (stareDorita == "0")
        digitalWrite(releuPompa, LOW);
    if (stareDorita == "1")
        digitalWrite(releuPompa, HIGH);
        
}

