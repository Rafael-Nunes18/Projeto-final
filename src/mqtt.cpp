#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <ezTime.h>
#include "internet.h"
#include <LiquidCrystal_I2C.h>
#include "ControleRemoto.h"

WiFiClient espClient;
PubSubClient client(espClient);

const char *mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char *mqtt_id = "esp32-senai134-teste";
const char *mqtt_topic_sub = "senai134/teste1/ouvindo";
const char *mqtt_topic_pub = "senai134/teste1/publicando";

void callback(char *, byte *, unsigned int);
void mqttConnect(void);
void tratamentoMsg(String);
void testeRecebimento(bool teste2);

void mqtt()
{
    Serial.begin(9600);
    conectaWiFi();

    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void testeconect()
{
    checkWiFi();

    if (!client.connected())
        mqttConnect();

    client.loop();

    static unsigned long tempoAnterior = 0;
    unsigned long agora = millis();

    static bool sistemaLigado = 1;

    JsonDocument doc;
    String mensagem;

    if (agora - tempoAnterior > 3000)
    {
        if (getLigado())
        {
            doc["Ligado"] = sistemaLigado;

            serializeJson(doc, mensagem);
            client.publish(mqtt_topic_pub, mensagem.c_str());

            tempoAnterior = agora;
        } else if (!getLigado()){
            doc["Desligado"] = !sistemaLigado;

            serializeJson(doc, mensagem);
            client.publish(mqtt_topic_pub, mensagem.c_str());

            tempoAnterior = agora;
        }
    }
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.printf("mensagem recebida em %s: ", topic);

    String mensagem = "";
    for (unsigned int i = 0; i < length; i++)
    {
        char c = (char)payload[i];
        mensagem += c;
    }
    Serial.println(mensagem);
    tratamentoMsg(mensagem);
}

void mqttConnect()
{
    while (!client.connected())
    {
        Serial.println("Conectando ao MQTT...");

        if (client.connect(mqtt_id))
        {
            Serial.println("Conectado com sucesso");
            client.subscribe(mqtt_topic_sub);
        }

        else
        {
            Serial.print("falha, rc=");
            Serial.println(client.state());
            Serial.println("tentando novamente em 5 segundos");
            delay(5000);
        }
    }
}

void tratamentoMsg(String msg)
{
    static String mensagem = msg;
    JsonDocument doc;
    DeserializationError erro = deserializeJson(doc, mensagem);

    if (erro)
    {
        Serial.println("Mensagem Recebida não esta no formato Json");
        return;
    }

    else
    {
        bool teste2 = 0;

        if (!doc["teste2"].isNull())
            teste2 = doc["teste2"];

        testeRecebimento(teste2);
    }
}

void testeRecebimento(bool teste2)
{
    Serial.println(teste2);
}
