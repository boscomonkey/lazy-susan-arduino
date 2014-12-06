#include <Servo.h>

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

void setup()
{
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  rndTurn(70, 90);
  rndDelay();

  rndTurn(120, 140);
  rndDelay();
}

void rndDelay()
{
  int ms = random(3000, 7000);

  Serial.print("delay:\t");
  Serial.println(ms);

  delay(ms);
}

void rndTurn(int low, int high)
{
  int angle = random(low, high);

  Serial.print("angle:\t");
  Serial.println(angle);

  myservo.write(angle);
}

