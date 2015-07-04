//-*- C -*-

/*
  pir-sensor-led

  Tracks output of PIR with LED.

  Also displays, in the console, milliseconds spent in a previous
  state when state transitions occur. Useful for observing the
  differences between RE-TRIGGER and NO-RE-TRIGGER.

  Inspired by http://playground.arduino.cc/Code/PIRsense
 */

// amount of time we give the sensor to calibrate (10-60 secs
// according to the datasheet)
int calibrationTime = 60;

int pirPin = 3;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;

int lastPir;
unsigned long lastTime;


void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(digitalRead(pirPin));
    delay(500);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");

  lastPir = digitalRead(pirPin);
  lastTime = millis();
}


void loop() {
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
}

