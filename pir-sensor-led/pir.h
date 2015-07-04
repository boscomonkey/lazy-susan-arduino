#ifndef PIR_H
#define PIR_H

#include <Arduino.h>

class PirTransitionListener
{
  public:
    virtual void onTransition(int pin, int fromState, int toState, unsigned long fromDuration) = 0;
};

class Pir
{
  public:

    Pir(int userPin);
    void init();
    void loop();
    int read();
    void registerListener(PirTransitionListener *ptl);

  private:

    int pirPin;
    int lastState;
    unsigned long lastTime;
    PirTransitionListener *plistener;
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

void Pir::registerListener(PirTransitionListener *ptl) {
  plistener = ptl;
}

#endif

