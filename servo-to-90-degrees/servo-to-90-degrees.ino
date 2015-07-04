//-*- C -*-

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

// multiply by degrees to get radians
//
const double degrees_to_radians = 0.0174532925;
const int DELAY_MS = 20;
const int DEGREE_INCREMENT = 1;
int degree = 90;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(degree);

  Serial.begin(9600);

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)

  Serial.print(degree);
  for (; degree < 150 ; degree += DEGREE_INCREMENT) {
    Serial.print(".");

    myservo.write(degree);
    delay(DELAY_MS);
  }
  Serial.print("\n");

  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW

  Serial.print(degree);
  for (; degree > 30 ; degree -= DEGREE_INCREMENT) {
    Serial.print(".");

    myservo.write(degree);
    delay(DELAY_MS);
  }
  Serial.print("\n");

}
