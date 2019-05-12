#include <Wire.h>  // i2c library
#include <Servo.h> // Motor library

/*
 * 90 - Initial and Not Moving
 * 87 - Lower Limit for Moving Backwards
 * 35 - Upper Limit for Moving Backwards
 * 93 - Lower Limit for Moving Forwards
 * 154 - Upper Limit for Moving Forwards
 */

// CODE HERE - Define Servo variables for each motor (ie. "Servo leftMotor;")
Servo motor5;
Servo motor6;
Servo motor7;
Servo motor8;

void setup()
{
  Serial.begin(9600);

  // CODE HERE - Initialize input and output pins
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  // CODE HERE - Attach to Motors and initialize to default position to reset the ESC.
  motor5.attach(5);
  motor6.attach(6);
  motor7.attach(7);
  motor8.attach(8);
  
  // CODE HERE - Initialize Serial communication.  We will be using the Serial Library for 
  // communication from topside controller so that we can debug in 
  // the Monitor or communicate with arduino
  Serial.begin(9600);
}

void loop()
{
 if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingInt = Serial.parseInt();
    if (incomingInt != 0) {
      Serial.println(incomingInt);
      motor5.write(incomingInt);
    }
  } 
}
