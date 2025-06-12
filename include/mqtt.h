#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>

void mqtt();
void testeconect();
void callback(char *topic, byte *payload, unsigned int length);
void mqttConnect();
void tratamentoMsg(String msg);
void testeRecebimento(bool teste2);

extern WiFiClient espClient;
extern PubSubClient client;

#endif
