// Sweep
// by BARRAGAN <>http://barraganstudio.com<>
// This example code is in the public domain.


#include <Servo.h>

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

int pos = 90;    // variable to store the servo position
int dir = -2;

void setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}


void loop()
{
  myservo.write(pos);
  pos += dir;
  delay(75);
  if (pos > 125) {
    dir *= -1;
    delay(3000);
  }
  if (pos < 35) {
    dir *= -1;
    delay(3000);
  }

}

