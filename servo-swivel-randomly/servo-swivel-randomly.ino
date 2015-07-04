//-*- C -*-

/*
 * Swivel servo in both directions with a random delta.
 */

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

// multiply by degrees to get radians
//
const double degrees_to_radians = 0.0174532925;
const int LIMIT_BOTTOM = 10;
const int LIMIT_TOP = 170;

int degree = (LIMIT_TOP - LIMIT_BOTTOM) / 2;
int direction = 1;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(degree);

  Serial.begin(9600);

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

void loop() {
  switch (direction) {
    int delta;

    case 1:
      degree = random(degree, LIMIT_TOP);
      break;
    case -1:
      degree = random(LIMIT_BOTTOM, degree);
      break;
  }

  Serial.print(direction);
  Serial.print("\t");
  Serial.println(degree);
  myservo.write(degree);

  direction *= -1;
  delay(2000);
}

