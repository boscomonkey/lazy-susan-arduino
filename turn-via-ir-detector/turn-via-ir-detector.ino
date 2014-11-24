//-*- C -*-

#include <Math.h>
#include <Servo.h>



Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created
int currAngle = 90;

// multiply by degrees to get radians
//
const double degrees_to_radians = 0.0174532925;


int rightLightPin = 4;    //connects the digital pin to the Light Detector Board's output
int leftLightPin = 2;    //connects the digital pin to the Light Detector Board's output

void setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(currAngle);

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  // initialize the input pins
  pinMode(rightLightPin, INPUT); 
  pinMode(leftLightPin, INPUT); 

  Serial.begin(9600);      // open the serial port at 9600 bps:
}

void loop() {
  delay(25);

  if (HIGH == digitalRead(leftLightPin) && LOW == digitalRead(rightLightPin)) {
    if (currAngle > 20) {
      currAngle -= 1;
      myservo.write(currAngle);
      
      Serial.print("LEFT: ");
      Serial.println(currAngle);
    }
  } else if (LOW == digitalRead(leftLightPin) && HIGH == digitalRead(rightLightPin)) {
    if (currAngle < 110) {
      currAngle += 1;
      myservo.write(currAngle);
      
      Serial.print("RIGHT: ");
      Serial.println(currAngle);
    }
  }
}
