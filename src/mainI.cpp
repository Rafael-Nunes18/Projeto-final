#include <Arduino.h>           //biblioteca padrao
#include <PubSubClient.h>      //biblioteca MQTT
#include <WiFi.h>              //biblioteca Wifi
#include <ezTime.h>            //biblioteca de fuso horario
#include <Wire.h>              //biblioteca LC2
#include <LiquidCrystal_I2C.h> //biblioteca lcd
#include <ArduinoJson.h>       //biblioteca para dados em formato JSON
#include <Bounce2.h>           //biblioteca para botoes
#include "internet.h"          // Biblioteca personalizada para conectar ao Wi-Fi

#define pinLed 2   // led
#define pinBotao 0 // botao

WiFiClient espClient;               // wifi
PubSubClient client(espClient);     // MQTT usando wifi
Bounce botao = Bounce();            // estabilizando o botao
Timezone tempo;                     // controle de fuso horario
LiquidCrystal_I2C lcd(0x27, 20, 4); // display

const char *mqtt_server = "broker.hivemq.com";                 // servidor publico do MQTT
const int mqtt_port = 1883;                                    // porta de seguranca
const char *mqtt_id = "esp32-senai134-catarina";               // id do usuario mqtt
const char *mqtt_topic_sub = "senai134/mesa06/esp_publicando"; // receber mensagens
const char *mqtt_topic_pub = "senai134/mesa06/esp_publicando"; // publicar mensagens

void mqttConnect(void);                      // conector do broker com o MQTT
void callback(char *, byte *, unsigned int); // funcao p receber mensagem do MQTT

void setup()
{
    lcd.init();          // iniciando o lcd
    lcd.backlight();     // acende o lcd
    lcd.setCursor(0, 0); // seta a localizacao do cursor
    lcd.print("ligado");

    pinMode(pinLed, OUTPUT);              // ativando o pin do led
    botao.attach(pinBotao, INPUT_PULLUP); // ativa botao

    Serial.begin(9600); // inicia o terminal

    conectaWiFi(); // conecta ao wifi

    client.setServer(mqtt_server, mqtt_port); // configuracao do servidor
    client.setCallback(callback);             // tratamento de mensagens

    waitForSync();                          // espera sincronizar o tempo
    tempo.setLocation("America/Sao_Paulo"); // escolhe a localizacao
}

void loop()
{
    checkWiFi();             // verifica conexao
    if (!client.connected()) // se o cliente nao estiver conectado
        mqttConnect();       // tenta conectar
    client.loop();           // mantem a conexao estavel
}

void callback(char *topic, byte *payload, unsigned int length)
{
    String mensagem = "";
    for (unsigned int i = 0; i < length; i++)
    {
        mensagem += (char)payload[i]; // conecta os bytes da mensagem recebida
    }

    Serial.print(mensagem); // exibe a mensagem

    JsonDocument doc;
    deserializeJson(doc, mensagem); // json se torna objeto

    lcd.setCursor(12, 0);
    lcd.print("mostra no lcd");
}

void mqttConnect()
{
    while (!client.connected()) // enquanto nao conectar
    {
        Serial.println("Conectando ao MQTT ...");

        if (client.connect(mqtt_id)) // tenta conectar
        {
            Serial.println("Conectado com sucesso!");
            client.subscribe(mqtt_topic_sub); // se inscreve no topico
        }
        else
        {
            Serial.print("Falha na conexao: ");
            Serial.println(client.state()); // mostra o erro
            Serial.println("Tentando novamente em 5 segundos...");
            delay(5000); // um crime necessario...
        }
    }
}