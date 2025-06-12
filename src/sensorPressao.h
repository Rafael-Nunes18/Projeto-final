#ifndef SENSOR_PRESSAO_H
#define SENSOR_PRESSAO_H

#include <Arduino.h>

extern bool alarmeSensorPressao;

void iniciarSensorPressao();
void atualizarSensorPressao();

#endif