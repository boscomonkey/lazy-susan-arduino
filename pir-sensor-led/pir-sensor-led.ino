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

// This listener class only cares about UP (i.e., 0 -> 1) transitions
//
class UpListener : public Pir::TransitionListener {
  public:
    virtual void onTransition(int pin, int fromState, int toState, unsigned long fromDuration);
  private:
    unsigned long lastUpTime = 0L;
};

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
  }
}

/*
 * global vars
 */
const int INVALID_PIN = -1;
const int LED_PIN = 13;
const int PIR_PINS[] = {2, 3};

Pir pir2 = Pir(2);
Pir pir3 = Pir(3);
UpListener listener2;
UpListener listener3;


void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  pir2.init();
  pir2.registerListener(&listener2);

  pir3.init();
  pir3.registerListener(&listener3);

  Serial.println("SENSOR ACTIVE");
}


void loop() {
  pir2.loop();
  pir3.loop();
}

