#include <Arduino.h>      //padrao arduino
#include <WiFi.h>         //para fazer a conexao wifi
#include <PubSubClient.h> //para fazer as publicacoes cliente
#include <ArduinoJson.h>  //para rodar o codigo em arquivo json
#include "internet.h"     // precisa conter conectaWiFi() e checkWiFi()

WiFiClient espClient;           // conecta o esp ao wifi
PubSubClient client(espClient); // objeto do cliente MQTT usando a conexão Wi-Fi

const char *mqtt_server = "broker.hivemq.com";                 // endereço do broker
const int mqtt_port = 1883;                                    // porta padrao MQTT
const char *mqtt_id = "esp32-senai134-catarina";               // indentificador do esp
const char *mqtt_topic_sub = "senai134/mesa04/esp_inscrito";   // topico em que o esp recebe
const char *mqtt_topic_pub = "senai134/mesa04/esp_publicando"; // topico em que o esp publica

// Variáveis de exemplo
unsigned long tempoEnvio = 5000; // intervalo de mensagens
bool envioMqtt = false;          // Flag para controlar se deve publicar

void callback(char *, byte *, unsigned int); // funcao chamada para receber mensagens
void mqttConnect(void);                      // função para conectar ao broker MQTT

void setup()
{
  Serial.begin(9600); // inicia a serial

  conectaWiFi(); // conecta a rede wifi internet.h

  client.setServer(mqtt_server, mqtt_port); // confgura o servidor MQTT
  client.setCallback(callback);             // chama a funcao callback quando receber mensagens
}

void loop()
{
  checkWiFi(); // confere se o wifi esta conectado

  if (!client.connected()) // se o cliente nao estiver conectado...
    mqttConnect();         // tenta conectar ao MQTT

  client.loop(); // mantem o client funcionando

  static unsigned long tempoAnterior = 0; // guarda o tempo da ultima mensagem enviada
  unsigned long agora = millis();         // armazena o tempo atual desde que o esp estava ligado

  if (agora - tempoAnterior > tempoEnvio) // se passou um determinado tempo desde a ultima mensagem
  {
    JsonDocument doc; // cria um json
    String mensagem;  // a mensagem chega em String

    serializeJson(doc, mensagem);                     // converte o json em string
    Serial.println(mensagem);                         // mostra a mensagem no monitor
    client.publish(mqtt_topic_pub, mensagem.c_str()); // publica no MQTT

    tempoAnterior = agora; // atualiza o tempo da mensagem
  }
}

void callback(char *topic, byte *payload, unsigned int length) // funcao callback
{
  Serial.printf("Mensagem recebida em %s: ", topic); // mostra o topico da mensagem recebida

  String mensagem = "";
  for (unsigned int i = 0; i < length; i++)
  {
    mensagem += (char)payload[i]; // transforma a mensagem em string
  }
  Serial.println(mensagem); // mostra a mensagem

  JsonDocument doc;
  deserializeJson(doc, mensagem); // torna o json em objeto

  if (!doc["tempoEnvio"].isNull()) // se a mensagem tem tempoEnvio att essa info
  {
    tempoEnvio = doc["tempoEnvio"];
  }
}

void mqttConnect()
{
  while (!client.connected()) // enquanto o MQTT nao conectar
  {
    Serial.println("Conectando ao MQTT..."); // mostrar essa mensagem na tela

    if (client.connect(mqtt_id)) // se o client conectar
    {
      Serial.println("Conectado com sucesso"); // mostra essa mensagem
      client.subscribe(mqtt_topic_sub);        // se inscreve no topico pra receber comandos
    }
    else
    {
      Serial.print("Falha, rc=");     // mostra a falha
      Serial.println(client.state()); // o estado da conexao
      Serial.println("Tentando novamente em 5 segundos");
      delay(5000); // tenta de novo em 5 seg
    }
  }
}
