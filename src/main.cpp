#include <Arduino.h>
#include "sensorMovimento.h"

void setup() {
  sensorMovimentoInit(); 
}

void loop() {
  sensorMovimento();
}
