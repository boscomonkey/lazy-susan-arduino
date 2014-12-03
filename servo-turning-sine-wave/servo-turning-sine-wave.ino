//-*- C -*-

#include <Math.h>
#include <Servo.h>

//
// CONSTANTS
//

// multiply by degrees to get radians
//
const double RADIANS_PER_DEGREE = 0.0174532925;

const int LEFT_LIMIT = 60;
const int RIGHT_LIMIT = 180;

// milliseconds to wait between servo movement: when servo is gently oscillating
const int GENTLE_DELAY = 45;

// milliseconds to wait between servo movement: when servo is shaking back & forth
const int SHAKE_DELAY = 10;

// maximum servo movement per iteration
const int ANGLE_INCREMENT = 5;

// milliseconds to wait at one end point before reversing rotation
const int TURN_AROUND_DELAY = 10;

// number of degrees to shake servo on each side of center
const int SHAKE_OFFSET_ANGLE = 25;

//
// GLOBALS
//

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

int currAngle = 135;

void setup()
{
  myservo.attach(9);   // attaches the servo on pin 9 to the servo object
  myservo.write(currAngle);

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  Serial.begin(9600);  // open the serial port at 9600 bps:

  delay(3000);         // wait long enough to open Serial console
}

void loop()
{
  // randomly determine which behavior
  int behaviorMode = random(4);
  Serial.print("BEHAVIOR MODE:\t");
  Serial.println(behaviorMode);

  switch (behaviorMode) {
    case 0:
    case 1:
    case 2:
      currAngle = oscillateGently(currAngle, random(3, 6));
      break;

    case 3:
      currAngle = shakeServo(currAngle, random(2, 4));
      break;
  }

  // wait random seconds until next loop
  int delayNext = random(1000, 5000);
  Serial.print("delayNext:\t");
  Serial.println(delayNext);

  delay(delayNext);
}

int oscillateGently(int angle, int numOscillations)
{
  int range;
  int skew;
  int limit;

  for (int ii = 0; ii < numOscillations ; ii += 1) {
    delay(TURN_AROUND_DELAY);
  
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    range = angle - LEFT_LIMIT;
    skew = random(random(range));
    limit = LEFT_LIMIT + skew;
    angle = turnServo(myservo, angle, limit, GENTLE_DELAY);

    Serial.println("---------------------------------------------------------------- LEFT");
    Serial.print("range: ");
    Serial.print(range);
    Serial.print("\tskewing: ");
    Serial.print(skew);
    Serial.print("\tlimit: ");
    Serial.print(limit);
    Serial.print("\tangle: ");
    Serial.println(angle);
  
    delay(TURN_AROUND_DELAY);
  
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    range = RIGHT_LIMIT - angle;
    skew = random(random(range));
    limit = RIGHT_LIMIT - skew;
    angle = turnServo(myservo, angle, limit, GENTLE_DELAY);

    Serial.println("---------------------------------------------------------------- RIGHT");
    Serial.print("range: ");
    Serial.print(range);
    Serial.print("\tskewing: ");
    Serial.print(skew);
    Serial.print("\tlimit: ");
    Serial.print(limit);
    Serial.print("\tangle: ");
    Serial.println(angle);
  }

  return angle;
}

int turnServo(Servo servo, int startAngle, int endAngle, int delayTime)
{
  int angle = startAngle;

  // turn right
  if (startAngle < endAngle) {
    while (angle < endAngle)
    {
      //      Serial.print("RIGHT:\t");
      //      Serial.println(angle);

      servo.write(angle);         // tell servo to go to position in variable 'angle'
      delay(delayTime);           // waits for the servo to reach the position

      angle += calcDeltaAngle(angle, startAngle, endAngle, ANGLE_INCREMENT);
    }
  }
  // turn left
  else if (startAngle > endAngle) {
    while (angle > endAngle)
    {
      //      Serial.print("LEFT:\t");
      //      Serial.println(angle);

      servo.write(angle);         // tell servo to go to position in variable 'angle'
      delay(delayTime);           // waits for the servo to reach the position

      // note decrement instead of increment
      angle -= calcDeltaAngle(angle, endAngle, startAngle, ANGLE_INCREMENT);
    }
  }
  // don't turn
  else {
    Serial.print("NO OP:\t");
    Serial.println(angle);
  }

  return angle;
}

// Rotate servo 'numShakes' back & forth, starting at 'startAngle'.
// Returns final angle of head
//
int shakeServo(int startAngle, int numShakes)
{
  int rightEnd = startAngle + SHAKE_OFFSET_ANGLE;
  int leftEnd = startAngle - SHAKE_OFFSET_ANGLE;

  turnServo(myservo, startAngle, leftEnd, SHAKE_DELAY);
  for (int ii = 0; ii < numShakes ; ii++)
  {
    turnServo(myservo, leftEnd, rightEnd, SHAKE_DELAY);
    turnServo(myservo, rightEnd, leftEnd, SHAKE_DELAY);
  }
  turnServo(myservo, leftEnd,  startAngle, SHAKE_DELAY);

  return startAngle;
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

  double rad = normalizedOffset * RADIANS_PER_DEGREE;
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


