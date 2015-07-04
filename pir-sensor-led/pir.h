#ifndef PIR_H
#define PIR_H

#include <Arduino.h>

class Pir
{
  public:

    class TransitionListener
    {
        void onEvent(Pir, int fromState, int toState, unsigned long fromDuration);
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
  unsigned long currTime = millis();

  // only check for transitions
  if (currState != lastState) {
    unsigned long elapsed = currTime - lastTime;

    Serial.print("pin:");
    Serial.print(pirPin);
    Serial.print("\t");

    Serial.print(lastState);
    Serial.print("->");
    Serial.print(currState);
    Serial.print("\t");

    Serial.println(elapsed);

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

