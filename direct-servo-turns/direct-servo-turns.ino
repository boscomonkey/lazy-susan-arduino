#include <Servo.h>

const int DETECTOR_LEFT = 3;
const int DETECTOR_RIGHT = 5;

const int HIGH_LIMIT = 140;
const int LOW_LIMIT = 70;
const int VARIATION = 20;

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

void setup()
{
  Serial.begin(9600);

  // initialize detector input pins
  pinMode(DETECTOR_LEFT, INPUT); 
  pinMode(DETECTOR_RIGHT, INPUT); 

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  delay(2000);        // give operator a chance to open console
}

void loop()
{
  checkEyes(HIGH_LIMIT, LOW_LIMIT, VARIATION);
  rndTurn(LOW_LIMIT, LOW_LIMIT + VARIATION);

  checkEyes(HIGH_LIMIT, LOW_LIMIT, VARIATION);
  rndTurn(HIGH_LIMIT - VARIATION, HIGH_LIMIT);
}

void checkEyes(int highLimit, int lowLimit, int variation)
{
  // set to true to skip this function
  if (false) {
    return;
  }

  int middle = (highLimit + lowLimit) / 2;
  int swing = variation / 2;
  int newLow = middle - swing;
  int newHigh = middle + swing;
  int angle = random(newLow, newHigh);

  while (true) {
    Serial.print("scan:");
    Serial.print(angle);

    if (angle < lowLimit || angle > highLimit) {
      break;
    }

    myservo.write(angle);

    Serial.print("\t");
    rndDelay(4000, 6000);

    Serial.print("\t");
    int rightValue = readDetector(DETECTOR_RIGHT, "right");
    Serial.print("\t");
    int leftValue = readDetector(DETECTOR_RIGHT, "left");

    if (HIGH == leftValue && LOW == rightValue) {
      // left side movement
      angle = random(angle - variation, angle);
    }
    else if (LOW == leftValue && HIGH == rightValue) {
      // right side movement
      angle = random(angle, angle + variation);
    }
    else if (HIGH == leftValue && HIGH == rightValue) {
      // both eyes busy - big swings left & right
      rndTurn(LOW_LIMIT, LOW_LIMIT + VARIATION);
      rndTurn(HIGH_LIMIT - VARIATION, HIGH_LIMIT);
      break;
    }
    else {
      break;
    }
  }

  Serial.print("\t");
}

void rndDelay(int loBound, int hiBound)
{
  int ms = random(loBound, hiBound);

  Serial.print("delay:");
  Serial.print(ms);

  delay(ms);
}

void rndTurn(int low, int high)
{
  int angle = random(low, high);

  Serial.print("angle:");
  Serial.print(angle);
  Serial.print("\t");

  myservo.write(angle);

  rndDelay(2000, 4000);
  Serial.println("");
}

int readDetector(int detectorPin, char* label)
{
  int detectorValue = digitalRead(detectorPin);

  Serial.print(label);
  Serial.print(":");
  Serial.print(detectorValue);

  return detectorValue;
}

