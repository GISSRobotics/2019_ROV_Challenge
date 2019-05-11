// SELECT 328P (old bootloader) WHEN USING USB C CONVERTER!

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
