#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Usa os pinos padrão do ESP32: GPIO21 (SDA), GPIO22 (SCL)

  // Inicializa o sensor
  if (!lox.begin()) {
    Serial.println("VL53L0X não encontrado. Verifique as conexões.");
    while (1);
  }
  Serial.println("VL53L0X iniciado com sucesso.");
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false); // false = sem debug na serial
  int distancia = measure.RangeMilliMeter/10;

  /*if (measure.RangeStatus != 4) {  // 4 = erro
    Serial.print("Distância: ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm");
    Serial.print(measure.RangeMilliMeter/10);
    Serial.println("CM");
  } else {
    Serial.println("Fora de alcance");
  }*/

 if(distancia > 30 && distancia < 50)
 {
  Serial.println("Entre 30 e 50");
 }
 if(distancia > 10 && distancia < 30)
 {
  Serial.println("Entre 10 e 30");
 }

  delay(500);
}
