#include "sensorPressao.h"
#include <HX711.h>

const int LOADCELL_DOUT_PIN = 5;
const int LOADCELL_SCK_PIN = 18;
const float LIMIAR_PESO = 5.0;                // Em kg
const unsigned long INTERVALO_LEITURA = 1000; // 1 segundo

HX711 scale;
bool alarmeSensorPressao = false;

unsigned long ultimoMillisLeitura = 0;

void iniciarSensorPressao()
{
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(41795); // Ajuste conforme calibrado
  delay(2000);
  scale.tare(); // Zera a balança
}

void atualizarSensorPressao()
{
  unsigned long agora = millis();
  if (agora - ultimoMillisLeitura >= INTERVALO_LEITURA)
  {
    ultimoMillisLeitura = agora;

    float medida = scale.get_units(5); // Média de 5 leituras
    alarmeSensorPressao = (medida > LIMIAR_PESO);

    scale.power_down();
    delayMicroseconds(100); // tempo mínimo recomendado pela doc
    scale.power_up();
  }
}
