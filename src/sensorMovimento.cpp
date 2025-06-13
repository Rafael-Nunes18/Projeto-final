#include "SensorMovimento.h"
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox;

bool alarmeSensorMovimento = false;

const unsigned long INTERVALO_LEITURA = 500;
unsigned long ultimoMillisMovimento = 0;

void iniciarSensorMovimento()
{
  Wire.begin();
  if (!lox.begin())
  {
    Serial.println("Falha ao iniciar VL53L0X. Verifique conexão!");
    while (1)
      ;
  }
}

void atualizarSensorMovimento()
{
  unsigned long agora = millis();
  if (agora - ultimoMillisMovimento >= INTERVALO_LEITURA)
  {
    ultimoMillisMovimento = agora;

    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);

    if (measure.RangeStatus != 4)
    { // 4 = erro de leitura
      int distanciaCM = measure.RangeMilliMeter / 10;

      Serial.print("Distância: ");
      Serial.print(distanciaCM);
      Serial.println(" cm");

      // Alarme se estiver entre 5 e 200 cm
      alarmeSensorMovimento = (distanciaCM >= 5 && distanciaCM <= 200);
    }
    else
    {
      Serial.println("Fora de alcance");
      alarmeSensorMovimento = false;
    }
  }
}
