#include <Arduino.h>
#include "ControleRemoto.h"

void setup() {
    Serial.begin(9600);
    initControleRemoto();
    pinMode(botao, INPUT);
}

void loop() {
    Controller();
}
