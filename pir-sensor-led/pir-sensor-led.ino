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

Pir pir = Pir(3);   //the digital pin connected to the PIR sensor's output

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pir = Pir(3);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(pir.read());
    delay(500);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");

  pir.init();
}


void loop() {
  pir.loop();

  /*
  int pirValue = digitalRead(pirPin);
  unsigned long nowTime = millis();

  // only check for transitions
  if (pirValue != lastPir) {
    unsigned long elapsed = nowTime - lastTime;

    Serial.print(elapsed);
    Serial.print("\t");
    Serial.println(lastPir);

    digitalWrite(ledPin, pirValue);

    lastPir = pirValue;
    lastTime = nowTime;
  }
   */
}

