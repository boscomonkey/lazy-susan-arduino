#include <Servo.h>

const int DETECTOR_LEFT = 3;
const int DETECTOR_RIGHT = 5;

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

void setup()
{
  Serial.begin(115200);  // 57600 * 2

  // initialize detector input pins
  pinMode(DETECTOR_LEFT, INPUT); 
  pinMode(DETECTOR_RIGHT, INPUT); 

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  rndTurn(70, 90);
  rndTurn(120, 140);
}

void rndDelay()
{
  int ms = random(4000, 7000);

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

  rndDelay();
  Serial.print("\t");

  readDetector(DETECTOR_LEFT, "left");
  Serial.print("\t");

  readDetector(DETECTOR_RIGHT, "right");
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

