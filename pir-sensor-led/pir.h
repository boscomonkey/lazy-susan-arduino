#ifndef PIR_H
#define PIR_H

#include <Arduino.h>

class Pir
{
  public:

    class TransitionListener {
      public:
        virtual void onTransition(int pin, int fromState, int toState, unsigned long fromDuration) = 0;
    };

    Pir(int userPin);
    void init();
    void loop();
    int read();
    void registerListener(TransitionListener *ptl);

  private:

    int pirPin;
    int lastState;
    unsigned long lastTime;
    TransitionListener *plistener;
};

Pir::Pir(int userPin) {
  pirPin = userPin;
  plistener = NULL;

  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);
}

void Pir::init() {
  lastState = digitalRead(pirPin);
  lastTime = millis();
}

void Pir::loop() {
  int currState = digitalRead(pirPin);

  // only check for transitions
  if (currState != lastState) {
    unsigned long currTime = millis();
    unsigned long elapsed = currTime - lastTime;

    if (NULL != plistener) {
      plistener->onTransition(pirPin, lastState, currState, elapsed);
    }

    lastState = currState;
    lastTime = currTime;
  }
}

int Pir::read() {
  return digitalRead(pirPin);
}

void Pir::registerListener(TransitionListener *ptl) {
  plistener = ptl;
}

#endif

