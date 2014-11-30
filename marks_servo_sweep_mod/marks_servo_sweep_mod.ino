// Sweep
// by BARRAGAN <>http://barraganstudio.com<>
// This example code is in the public domain.


#include <Servo.h>
#include <Math.h>

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

int pos = 90;    // variable to store the servo position
int dir = -2;

// multiply by degrees to get radians
//
const double RADIANS_PER_DEGREE = 0.0174532925;

const int LEFT_LIM = 35;
const int RIGHT_LIM = 125;
// milliseconds to wait between servo movement: when servo is gently oscillating



void setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}


void loop()
{
  myservo.write(pos);
  pos += dir;
  rand_delay(65, 20);
  if (pos > RIGHT_LIM) {
    dir *= -1;
    rand_delay(1500,1500);
  }
  if (pos < LEFT_LIM) {
    dir *= -1;
    rand_delay(1500,1500);
  }

}

int rand_delay(int min_time, int rand_range){
  int r = random(rand_range);
  int del = min_time + rand_range;
  delay(del);
}

