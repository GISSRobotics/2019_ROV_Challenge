#include <Wire.h>  // i2c library
#include <Servo.h> // Motor library

// CODE HERE - Define Servo variables for each motor (ie. "Servo leftMotor;")

// CODE HERE - Define pin number constants to be used (ie. "const int LED_PIN = 9;")

// CODE HERE - Define any other variables that you want to use everywhere (if they are 
// only needed temporarily, define them in functions so that it doesn't take up more program memory)

String receivedKey;
int receivedInteger;
float receivedFloat;
String receivedString;


void setup()
{
  // CODE HERE - Initialize input and output pins

  // CODE HERE - Initialize starting values for outputs (ie LED on or off)

  // CODE HERE - Attach to Motors and initialize to default position to reset the ESC.


  // CODE HERE - Initialize Serial communication.  We will be using the Serial Library for 
  // communication from topside controller so that we can debug in 
  // the Monitor or communicate with arduino
  Serial.begin(9600);

  // CODE HERE - Send any starting info youd like to send to the controller (ie Robot name)
     sendString("string", "another string");
     sendInt("integer", 7);
     sendFloat("float", 6);
  
      
  // CODE HERE - Initialize I2C communication.  We will be using this to communicate with I2C
  // sensors or other arduinos inside the ROV. 
}

void loop()
{
  readAndSendSensorData();

  while (receiveMessage()){
    processReceivedMessage();
  }
}

void readAndSendSensorData(){
  // CODE HERE - Read each of your sensors and send them to the controller
  // example: sendFloat("Water Depth", analogRead(DEPTH_SENSOR));
  // you can also choose to do other actions based on the values here, not just send them
}

void processReceivedMessage(){
  sendString("receivedstring:" ,receivedString );
  sendInt(receivedInteger);
  sendFloat(receivedFloat);
  // CODE HERE - There should be values in the variables receivedKey, received(Integer, Float & String)
  // do whatever action you want based on that message. Example: 
  // if (receivedKey == "PS2 Button" && receivedString == "X"){
  //     setMotorSpeed(MOTORH1, 0);
  //     setMotorSpeed(MOTORH2, 0);
  //     setMotorSpeed(MOTORV1, 0);
  //     setMotorSpeed(MOTORV2, 0);
  // }
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
  receivedKey = Serial.readStringUntil('-');
  // CODE HERE - read the data type char
  char dataType = Serial.read();
  // CODE HERE - read the value in different ways depending on the data type char.
  // You can use an if statement or look into how to use a "switch statement"
  // BRYNS NOTE, when i write INSERT that is a placeholder for code, if any. 


  
switch (dataType) {
 
  case 'I':
    receivedInteger = Serial.parseInt(/*INSERT*/);  
    break;   
  case 'F':
    receivedFloat = Serial.parseFloat(/*INSERT*/);
    break;
  case 'S':
    receivedString = Serial.readStringUntil('\n');
    break;
   
}
  
  // YAY!  we got to the end which means we stored the message lets report that back
  return true;
}

void sendKeyAndType(String key, char typeChar){
  Serial.print('~');
  Serial.print(key);
  Serial.print('-');
  Serial.print(typeChar);
  Serial.print('-');
}
void sendFloat(String key, float val){
  sendKeyAndType(key, 'F');
  Serial.println(val);
}
void sendInt(String key, int val){
  sendKeyAndType(key, 'I');
  Serial.println(val);
}
void sendString(String key, String val){
  sendKeyAndType(key, 'S');
  Serial.println(val);
}
