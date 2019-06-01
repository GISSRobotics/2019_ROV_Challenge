#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_LSM303.h>
#include <SparkFun_MS5803_I2C.h>
#include <Wire.h>

MS5803 sensor(ADDRESS_HIGH);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

float temperature_C;
double pressure_abs;

void setup() {
  // put your setup code here, to run once:

  //Communication
  Wire.begin();
  Serial.begin(9600);

  // Pressure Sensor
  sensor.reset();
  sensor.begin();
  reset();

  // Magnet Sensor
  mag.enableAutoRange(true);
  mag.begin();

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

  magnet_readings();
}

void reset() {
  Wire.beginTransmission(0x76);
  Wire.write(0x1E);
  Wire.endTransmission();
}

void magnet_readings() {
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);

  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  /* Note: You can also get the raw (non unified values) for */
  /* the last data sample as follows. The .getEvent call populates */
  /* the raw values used below. */
  // Serial.print("X Raw: "); Serial.print(mag.raw.x); Serial.print("  ");
  // Serial.print("Y Raw: "); Serial.print(mag.raw.y); Serial.print("  ");
  // Serial.print("Z Raw: "); Serial.print(mag.raw.z); Serial.println("");

  /* Delay before the next sample */
  delay(500);
}
