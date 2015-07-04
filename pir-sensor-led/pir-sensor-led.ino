//-*- C -*-

/*
  pir-sensor-led

  Tracks output of PIR with LED.

  Also displays, in the console, milliseconds spent in a previous
  state when state transitions occur. Useful for observing the
  differences between RE-TRIGGER and NO-RE-TRIGGER.

  Inspired by http://playground.arduino.cc/Code/PIRsense
 */

#include "pir.h"

// amount of time we give the sensor to calibrate (10-60 secs
// according to the datasheet)
const int calibrationTime = 60;
const int ledPin = 13;

// simple listener class to display PIR transitions
class SimpleListener : public Pir::TransitionListener {
  public:
    virtual void onTransition(int pin, int fromState, int toState, unsigned long fromDuration);
};

void SimpleListener::onTransition(int pin, int fromState, int toState, unsigned long fromDuration) {
  Serial.print("pin:");
  Serial.print(pin);
  Serial.print("\t");

  Serial.print(fromState);
  Serial.print("->");
  Serial.print(toState);
  Serial.print("\t");

  Serial.println(fromDuration);

  // show PIR state on LED also
  digitalWrite(ledPin, toState);
}

/*
 * global vars
 */
Pir pir(3);                 // PIR is connected to pin 3
SimpleListener listener;


void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(pir.read());
    delay(500);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");

  pir.init();
  pir.registerListener(&listener);
}


void loop() {
  pir.loop();
}

