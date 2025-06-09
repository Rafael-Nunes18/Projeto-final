#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();


void sensorMovimento() {
  Serial.begin(9600);
  Wire.begin();

  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false); 
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
