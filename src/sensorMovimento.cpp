#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox;



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

  int distancia = measure.RangeMilliMeter / 10;

 /* if (distancia > 30 && distancia < 50) {
    Serial.println("Entre 30 e 50");
  }
  if (distancia > 10 && distancia < 30) {
    Serial.println("Entre 10 e 30");
  }

  */
  if (measure.RangeStatus != 4) {  // 4 = erro
    Serial.print("Distância: ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm");
    Serial.print(measure.RangeMilliMeter/10);
    Serial.println("CM");
  } else {
    Serial.println("Fora de alcance");
  }
  delay(500);
}

