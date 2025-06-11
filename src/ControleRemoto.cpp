#include "ControleRemoto.h"
#include <Arduino.h>
#include <Bounce2.h>

Bounce botaoDebounce = Bounce();
bool ligado = false;

void initControleRemoto() {
    pinMode(botao, INPUT_PULLUP);      
    botaoDebounce.attach(botao);       
    botaoDebounce.interval(25);        
}

void Controller()
{
    botaoDebounce.update(); // Atualiza o estado do botão

    if (botaoDebounce.fell()) { // Detecta quando o botão foi pressionado
        ligado = !ligado;

        if (ligado)
            Serial.println("Ligado!");
        else
            Serial.println("Desligado!");
    }
}