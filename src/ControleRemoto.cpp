#include "ControleRemoto.h"
#include <Arduino.h>
#include <Bounce2.h>

Bounce botaoDebounce = Bounce();
static bool ligado = false;

void initControleRemoto()
{
    pinMode(botao, INPUT_PULLUP);
    pinMode(pinLed, OUTPUT);
    botaoDebounce.attach(botao);
    botaoDebounce.interval(25);
}

void Controller()
{
    botaoDebounce.update();

    if (botaoDebounce.fell())
    {
        ligado = !ligado;

        if (getLigado())
        {
            digitalWrite(pinLed, HIGH);
            Serial.println("Sistema Ativado!");
            Serial.println("Portas Fechadas!");
        }
        else
        {
            digitalWrite(pinLed, LOW);
            Serial.println("Sistema Desativado!");
            Serial.println("Portas Abertas!");
        }
    }
}

bool getLigado(){
    return ligado;
}