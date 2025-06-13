#ifndef CONTROLLEREMOTO_H
#define CONTROLLEREMOTO_H

#include <Arduino.h>

#define botao 0
#define pinLed 2

bool getLigado();
void Controller();
void initControleRemoto();

#endif