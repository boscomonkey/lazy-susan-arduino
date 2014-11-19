#include <Math.h>
#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
const double degrees_to_radians = 0.0174532925;

//int pos = 0;    // variable to store the servo position 

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(90);
}

void loop() 
{ 
  const int delayTime = 25;
  const int startPoint = 5;
  const int endPoint = 175;
  const int increment = 3;
  const int turnaroundTime = 10;
  int pos = 0;
    
  delay(turnaroundTime);

  for(pos = startPoint; pos < endPoint; )  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);     // tell servo to go to position in variable 'pos' 
    delay(delayTime);                       // waits 15ms for the servo to reach the position 
    
    float rad = pos * degrees_to_radians;
    int increAngle = ceil(increment * sin(rad));

    pos += increAngle;
  } 
  
  delay(turnaroundTime);
  
  for(pos = endPoint; pos > startPoint; )     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(delayTime);                       // waits 15ms for the servo to reach the position 
    
    float rad = pos * degrees_to_radians;
    int increAngle = ceil(increment * sin(rad));

    pos -= increAngle;
  } 
} 
