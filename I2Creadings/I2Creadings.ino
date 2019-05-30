#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  reset();
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(0x76);
  Wire.write(0x48);
  Wire.endTransmission();
  Wire.beginTransmission(0x76);
  Wire.write(0x00);
  Wire.endTransmission();
  
  int response;
  
  byte b = Wire.read();
  response = b << 16;
  byte b = Wire.read();
  response |= b << 8;
  byte b = Wire.read();
  response |= b;
  Serial.print(b);
  
  
  delay(100);
}

void reset() {
  Wire.beginTransmission(0x76);
  Wire.write(0x1E);
  Wire.endTransmission();
}

