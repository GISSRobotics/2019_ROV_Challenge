#include <SparkFun_MS5803_I2C.h>
#include <Wire.h>

MS5803 sensor(ADDRESS_HIGH);

float temperature_C;
double pressure_abs;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  sensor.reset();
  sensor.begin();
  reset();
} 

void loop() {
  // put your main code here, to run repeatedly:

  /*
  Wire.beginTransmission(0x76);
  Wire.write(0x48);
  Wire.endTransmission();
  delay(500);
  Wire.beginTransmission(0x76);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(500);
  
  uint32_t response;
  
  byte b = Wire.read();
  response = (uint32_t)b << 16;
  b = Wire.read();
  response |= (uint32_t)b << 8;
  b = Wire.read();
  response |= (uint32_t)b;
  Serial.println(response);
  */

  temperature_C = sensor.getTemperature(CELSIUS, ADC_4096);
  Serial.println(temperature_C);

  pressure_abs = sensor.getPressure(ADC_4096);
  Serial.println(pressure_abs);
  
  delay(100);
}

void reset() {
  Wire.beginTransmission(0x76);
  Wire.write(0x1E);
  Wire.endTransmission();
}
