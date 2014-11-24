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

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  Serial.begin(9600);      // open the serial port at 9600 bps:
}

void loop()
{
  const int startAngle = 20;
  const int endAngle = 130;

  // milliseconds to wait between servo movement
  const int delayTime = 30;

  // maximum servo movement per iteration
  const int increment = 3;

  // milliseconds to wait at one end point before reversing rotation
  const int turnaroundTime = 10;

  int angle = 0;

  delay(turnaroundTime);

  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  for(angle = startAngle; angle < endAngle; )
  {
    myservo.write(angle);       // tell servo to go to position in variable 'angle'
    delay(delayTime);           // waits for the servo to reach the position

    angle += calcDeltaAngle(angle, startAngle, endAngle, increment);
  }

  delay(turnaroundTime);

  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  for(angle = endAngle; angle > startAngle; )
  {
    myservo.write(angle);       // tell servo to go to position in variable 'angle'
    delay(delayTime);           // waits for the servo to reach the position

    // note decrement instead of increment
    angle -= calcDeltaAngle(angle, startAngle, endAngle, increment);
  }
}

int calcDeltaAngle(int angle, int startAngle, int endAngle, int maxAngleIncrement)
{
  // normal half circle is 180 degrees
  const double wholeRange = 180.0;

  // amount to rotate head depends on where it is: more in the
  // middle, & less at the ends. AKA sine wave.
  int currRange = endAngle - startAngle;
  double rangeRatio = wholeRange / currRange;
  int offsetAngle = angle - startAngle;
  double normalizedOffset = rangeRatio * offsetAngle;

  double rad = normalizedOffset * degrees_to_radians;
  double sineValue = sin(rad);
  int increAngle = ceil(0.1 + maxAngleIncrement * sineValue);

  /*
  Serial.print(angle);
  Serial.print("\t");
  Serial.print(increAngle);
  Serial.println("");
  */

  return increAngle;
}


