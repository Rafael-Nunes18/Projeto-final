#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox;

bool alteracaoMovimento = 0;



void sensorMovimentoInit() {
  Serial.begin(9600);
  Wire.begin();
  
  if (!lox.begin()) {
    Serial.println("Falha ao iniciar VL53L0X. Verifique conexão!");
    while (1); 
  }
}

void sensorMovimento() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  int distanciaMovimento = measure.RangeMilliMeter / 10;
 
  /*if (measure.RangeStatus != 4) {  // 4 = erro
    Serial.print("Distância: ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm");
    Serial.print(measure.RangeMilliMeter/10);
    Serial.println("CM");
  } else {
    Serial.println("Fora de alcance");
  }*/

  if(distanciaMovimento >30 && distanciaMovimento < 40)
  {
    alteracaoMovimento = 0;
  }
  else 
  {
    alteracaoMovimento = 1;
  }

  Serial.println(alteracaoMovimento);
}

