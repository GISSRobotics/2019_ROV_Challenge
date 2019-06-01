#include <Adafruit_Sensor.h> // Compass lib
#include <Adafruit_LSM303_U.h> // Compass lib
#include <Adafruit_LSM303.h> // Compass lib
#include <SparkFun_MS5803_I2C.h> // Pressure lib
#include <Wire.h>  // i2c lib
#include <Servo.h> // Motor lib

// Motors
Servo motorFL; // pin 5
Servo motorFR; // pin 6
Servo motorBL; // pin 7
Servo motorBR; // pin 8

// Compass Sensor
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

// Acceleration Sensor
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

// Pressure Sensor
MS5803 sensor(ADDRESS_HIGH);

int HistoryValue = 0;
char printBuffer[128];
void setup()
{
  // Initialise Motors
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  motorFL.attach(5);
  motorFR.attach(6);
  motorBL.attach(7);
  motorBR.attach(8);

  resetMotor(motorFL);
  resetMotor(motorFR);
  resetMotor(motorBL);
  resetMotor(motorBR);

  // Initialise Communications
  Serial.begin(9600);
  Wire.begin();

  // Initialise Pressure Sensor
  sensor.reset();
  sensor.begin();
  resetPressureSensor();

  // Initialise Compass
  mag.enableAutoRange(true);
  mag.begin();

  // Initialise Accelerometer
  accel.begin();
}

void loop()
{
  readAndSendSensorData();

  while (receiveMessage()){
    processReceivedMessage();
  }
}

void readAndSendSensorData() {
  // example: sendFloat("Water Depth", analogRead(DEPTH_SENSOR));
  sendFloat("Temperature:", readTemperature());
  sendFloat("Pressure:", readPressure());

  sendFloat("Compass X:", readCompassX());
  sendFloat("Compass Y:", readCompassY());
  sendFloat("Compass Z:", readCompassZ());
  sendFloat("Compass Angle:", readCompassAngle());

  sendFloat("Acceleration X:", readAccelerationX());
  sendFloat("Acceleration Y:", readAccelerationY());
  sendFloat("Acceleration Z:", readAccelerationZ());
}

/**************
 * MOTOR CODE *
 **************/

void resetMotor(Servo motor) {
  motor.write(90);
}

void setMotorSpeedInPercent(int percent, Servo motor) {
  if (percent == 0) {
    resetMotor(motor);
  }
  if (percent > 0) {
    int scale50 = percent / 2;
    int motorValue = 93 + scale50;
    motor.write(motorValue);
  }
  if (percent < 0) {
    int scale50 = percent / 2 * (-1);
    int motorValue = 87 - scale50;
    motor.write(motorValue);
  }
}

/***************
 * SENSOR CODE *
 ***************/

int readTemperature() {
  float temperature_C = sensor.getTemperature(CELSIUS, ADC_4096);
  return temperature_C;
}

int readPressure() {
  double pressure_abs = sensor.getPressure(ADC_4096);
  return pressure_abs;
}

void resetPressureSensor() {
  Wire.beginTransmission(0x76);
  Wire.write(0x1E);
  Wire.endTransmission();
}

int readCompassX() {
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);
  return event.magnetic.x;
}

int readCompassY() {
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);
  return event.magnetic.y;
}

int readCompassZ() {
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);
  return event.magnetic.z;
}

int readCompassAngle() {
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);
  return atan2(event.magnetic.y, event.magnetic.x) * 180 / PI;
}

int readAccelerationX() {
  /* Get a new sensor event */
  sensors_event_t event;
  accel.getEvent(&event);

  return event.acceleration.x;
}

int readAccelerationY() {
  /* Get a new sensor event */
  sensors_event_t event;
  accel.getEvent(&event);

  return event.acceleration.y;
}

int readAccelerationZ() {
  /* Get a new sensor event */
  sensors_event_t event;
  accel.getEvent(&event);

  return event.acceleration.z;
}

/**********************
 * COMMUNICATION CODE *
 **********************/

// Complete the methods below to allow sending key value pairs to the controller.
// We hope to have a common controller to make things easier, we will include a start
// character '~' and an end charater '\n' that will allow us to recover easily if there
// is ever a problem with the communication.  We also use the dash ('-') character to separate
// different parts of the message when reading. We want to send a readable string that describes
// the data to be sent, a type of data and the actual value.
// The format should be "~<key>-<typeChar>-<value>"
// String example: "~Robot Name-S-A^3 + B^2 + Z\n"
// Integer example: "~Motor#1 Speed-I-120\n"
// Float example: "~Battery Voltage-F-4.56\n"
// If you want more types (like byte, boolean, etc) we can discuss adding them to the protocol

// For reading from the controller we'll use the same protocol but we havent yet agreed on what commands
// will exist.  It will likely be a different values for each button and joystick on the PS2 controller
// regardless I've included some holding variables here to fill so that the reading code doesn't need to
// be the same as the processing code

String receivedKey;
int receivedInteger;
float receivedFloat;
String receivedString;

void processReceivedMessage(){
  // CODE HERE - There should be values in the variables receivedKey, received(Integer, Float & String)
  // do whatever action you want based on that message. Example:
  // if (receivedKey == "PS2 Button" && receivedString == "X"){
  //     setMotorSpeed(MOTORH1, 0);
  //     setMotorSpeed(MOTORH2, 0);
  //     setMotorSpeed(MOTORV1, 0);
  //     setMotorSpeed(MOTORV2, 0);
  // }

  if (receivedKey == "Motor FL") {
    setMotorSpeedInPercent(receivedInteger, motorFL);
  }
  if (receivedKey == "Motor FR") {
    setMotorSpeedInPercent(receivedInteger, motorFR);
  }
  if (receivedKey == "Motor BL") {
    setMotorSpeedInPercent(receivedInteger, motorBL);
  }
  if (receivedKey == "Motor BR") {
    setMotorSpeedInPercent(receivedInteger, motorBR);
  }
}

boolean receiveMessage(){
  // read a message from the controller (if it exists) in the
  // proper format into the above variables
  // Helpful functions to look into in the Serial library:
  // readStringUntil(), parseInt(), parseFloat(), read(), available()
  // return value - If there is nothing to read or some error in the format then return false
  //                If you successfully read and store a whole message return true

  // Read until you read the start character
  while (Serial.available() && Serial.read() != '~');

  // The following line is safe to include before you are about to read anything you expect to be there
  if(!Serial.available()) return false;

  // CODE HERE - read the key
  String receivedKey = Serial.readStringUntil('-');

  // CODE HERE - read the data type char
  String type = Serial.readStringUntil('-');

  // CODE HERE - read the value in different ways depending on the data type char.
  // You can use an if statement or look into how to use a "switch statement"
  if (type == "S") {
    receivedString = Serial.read();
  } else if (type == "I") {
    receivedInteger = Serial.parseInt();
  } else if (type == "F") {
    receivedFloat = Serial.parseFloat();
  }

  // YAY!  we got to the end which means we stored the message lets report that back
  return true;
}

void sendKeyAndType(String key, char typeChar) {
  // CODE HERE - Send the message except for the value in the format "~<KEY>-<Type Char>-"
  // (see: Serial.print)
  Serial.print("~");
  Serial.print(key);
  Serial.print("-");
  Serial.print(typeChar);
  Serial.print("-");
}

void sendFloat(String key, float val){
  sendKeyAndType(key, 'F');
  // CODE HERE - Send the float value and a newline (See: Serial.println)
  Serial.println(val);
}

void sendInt(String key, int val){
  sendKeyAndType(key, 'I');
  // CODE HERE - Send the float value and a newline (See: Serial.println)
  Serial.println(val);
}

void sendString(String key, String val){
  sendKeyAndType(key, 'S');
  // CODE HERE - Send the float value and a newline (See: Serial.println)
  Serial.println(val);
}
