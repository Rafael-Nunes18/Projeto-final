#include <Arduino.h>
#include "internet.h"
#include "mqtt.h"
#include "ControleRemoto.h"

void setup()
{
  Serial.begin(9600);
  mqtt();              
  mqttConnect();
  initControleRemoto();

  String msg = "{\"teste2\": true}";
  tratamentoMsg(msg);
}

void loop()
{
  Controller();
  testeconect(); 
   
}
