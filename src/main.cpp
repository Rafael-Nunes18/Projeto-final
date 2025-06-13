#include <Arduino.h>
#include "internet.h"
#include "mqtt.h"

void setup()
{
  Serial.begin(9600);
  mqtt();               // Inicializa conexão Wi-Fi e MQTT
  mqttConnect();        // Garante conexão com o broker

  // Teste de tratamento de mensagem JSON recebida
  String msg = "{\"teste2\": true}";
  tratamentoMsg(msg);
}

void loop()
{
  testeconect(); // Mantém conexão e publica mensagens periodicamente
}
