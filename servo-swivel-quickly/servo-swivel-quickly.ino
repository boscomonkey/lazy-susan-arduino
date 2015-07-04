//-*- C -*-

/*
 * Swivel servo quickly from bottom limit to top and back.
 */

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

const int LIMIT_BOTTOM = 10;
const int LIMIT_TOP = 170;

int degree = LIMIT_BOTTOM;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(degree);

  Serial.begin(9600);

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

// void loop() {}

void loop() {
  switch (degree) {
    case LIMIT_BOTTOM:
      degree = LIMIT_TOP;
      break;
    case LIMIT_TOP:
      // no break
    default:
      degree = LIMIT_BOTTOM;
      break;
  }

  Serial.println(degree);
  myservo.write(degree);

  delay(2000);
}

