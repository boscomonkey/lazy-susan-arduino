//-*- C -*-

#include <Math.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

// multiply by degrees to get radians
//
const double degrees_to_radians = 0.0174532925;

void setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);
}

void loop()
{
  const int startAngle = 10;
  const int endAngle = 170;

  // milliseconds to wait between servo movement
  const int delayTime = 25;

  // maximum servo movement per iteration
  const int increment = 3;

  // milliseconds to wait at one end point before reversing rotation
  const int turnaroundTime = 25;

  int angle = 0;

  delay(turnaroundTime);

  for(angle = startAngle; angle < endAngle; )
  {
    myservo.write(angle);       // tell servo to go to position in variable 'angle'
    delay(delayTime);           // waits for the servo to reach the position

    // amount to rotate head depends on where it is: more in the
    // middle, & less at the ends. AKA sine wave.
    float rad = angle * degrees_to_radians;
    int increAngle = ceil(increment * sin(rad));

    angle += increAngle;
  }

  delay(turnaroundTime);

  for(angle = endAngle; angle > startAngle; )
  {
    myservo.write(angle);       // tell servo to go to position in variable 'angle'
    delay(delayTime);           // waits for the servo to reach the position

    float rad = angle * degrees_to_radians;
    int increAngle = ceil(increment * sin(rad));

    // note decrement instead of increment
    angle -= increAngle;
  }
}
