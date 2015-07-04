//-*- C -*-

/*
 * Swivel servo slowly (1 degree at a time) from bottom limit to top
 * and back over and over.
 */

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

// multiply by degrees to get radians
//
const double degrees_to_radians = 0.0174532925;

const int lowLimit = 10;
const int highLimit = 170;
const int turnDelay = 50;

void setup() {
  Serial.begin(9600);  // open the serial port at 9600 bps:

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);
  for (int angle = 90; angle >= lowLimit ; angle--)
  {
    myservo.write(angle);
    Serial.println(angle);
    delay(turnDelay);
  }

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

void loop() {
  int angle = lowLimit;

  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  for (; angle <= highLimit ; angle++)
  {
    myservo.write(angle);
    Serial.println(angle);
    delay(turnDelay);
  }

  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  for (; angle >= lowLimit ; angle--)
  {
    myservo.write(angle);
    Serial.println(angle);
    delay(turnDelay);
  }
}
