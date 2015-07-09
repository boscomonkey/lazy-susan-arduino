//-*- C -*-

/*
  pir-sensor-led

  Tracks output of PIR with LED.

  Also displays, in the console, milliseconds spent in a previous
  state when state transitions occur. Useful for observing the
  differences between RE-TRIGGER and NO-RE-TRIGGER.

  Inspired by http://playground.arduino.cc/Code/PIRsense
 */

#include <Servo.h>
#include "pir.h"

// This listener class only cares about UP (i.e., 0 -> 1) transitions
//
class UpListener : public Pir::TransitionListener {
  public:
    const int degreeVariance = 10;

    UpListener(Servo *pservo, int degree);
    virtual void onTransition(int pin, int fromState, int toState, unsigned long fromDuration);
  private:
    unsigned long lastUpTime;
    Servo *pMyServo;
    int degreeHeading;
};

UpListener::UpListener(Servo *pservo, int degree) {
  lastUpTime = 0L;
  pMyServo = pservo;
  degreeHeading = degree;
}

void UpListener::onTransition(int pin, int fromState, int toState, unsigned long fromDuration) {
  if (LOW == fromState && HIGH == toState) {
    unsigned long currTime = millis();

    Serial.print("pin:");
    Serial.print(pin);

    if (0L != lastUpTime) {
      unsigned long elapsed = currTime - lastUpTime;

      Serial.print("\t");
      Serial.print(elapsed);
    }

    Serial.println("");
    lastUpTime = currTime;

    pMyServo->write(random(degreeHeading-degreeVariance, degreeHeading+degreeVariance));
  }
}

/*
 * global vars
 */

const int INITIAL_DEGREE = 90;
const int LED_PIN = 13;
const int SERVO_PIN = 9;

Pir pir2(2);
Pir pir3(3);
Pir pir4(4);
Pir pir5(5);
Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created
UpListener listener2(&myservo, 165);
UpListener listener3(&myservo, 120);
UpListener listener4(&myservo, 75);
UpListener listener5(&myservo, 30);

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  myservo.attach(SERVO_PIN);
  myservo.write(INITIAL_DEGREE);

  pir2.init();
  pir2.registerListener(&listener2);

  pir3.init();
  pir3.registerListener(&listener3);

  pir4.init();
  pir4.registerListener(&listener4);

  pir5.init();
  pir5.registerListener(&listener5);

  Serial.println("SENSOR ACTIVE");
}


void loop() {
  pir2.loop();
  pir3.loop();
  pir4.loop();
  pir5.loop();
}

