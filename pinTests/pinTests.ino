// SELECT 328P (old bootloader) WHEN USING USB C CONVERTER!

/*
 * To test RX-TX:
 * Connect USB to FTTI to Tether in reverse. RX to TX and TX to RX. GND to GND
 * If Serial Monitor outputs something, the Tether works.
 * 
 * To test Motors:
 * Connect Buzzer to Motor Pins.
 * D5 will beep every 12ms
 * D6 will beep every 25ms
 * D7 will beep every 50ms
 * D8 will beep every 75ms
 * 
 * To test I2C:
 * Connect Photo Resistor to I2C
 * -> Signal to pin to be tested (either top A4 or bottom A5)
 * -> GND to GND (third from top)
 * -> 5V to 3V3 (second from top)
 * If the output in the Serial Monitor changes correctly, the I2C is working.
 * 
 * To test Battery:
 * Connect Battery to board
 * -> Battery and Serial can be safely connected at the same time
 * A7 will output battery voltage
 */

int BUZZER5 = 5;
int BUZZER6 = 6;
int BUZZER7 = 7;
int BUZZER8 = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  beepMotors();
  readI2C(100);
  readBattery(100);
}

void beepMotors() {
  beep(BUZZER5, 12);
  beep(BUZZER5, 12);
  beep(BUZZER5, 12);

  beep(BUZZER6, 25);
  beep(BUZZER6, 25);
  beep(BUZZER6, 25);
  
  beep(BUZZER7, 50);
  beep(BUZZER7, 50);
  beep(BUZZER7, 50);
  
  beep(BUZZER8, 75);
  beep(BUZZER8, 75);
  beep(BUZZER8, 75);
}

void beep(int pin, int frequency) {
  Serial.println(pin);
  digitalWrite(pin, HIGH); // sets the digital pin 13 on
  delay(frequency);            // waits for a second
  digitalWrite(pin, LOW);  // sets the digital pin 13 off
  delay(frequency);  
}

void readI2C(int frequency) {
  Serial.print("A4:");
  Serial.println(analogRead(A4));
  Serial.print("A5:");
  Serial.println(analogRead(A5));
  delay(100);
}

void readBattery(int frequency) {
  Serial.print("A7:");
  Serial.println(analogRead(A7));
  delay(100);
}
