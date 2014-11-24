//********************************************************************************
// * File Name          : Light_detector
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/02/24
// * Description        : Turns an LED ON when the sensor detects the specified amount of light; otherwise LED remains OFF.
// ********************************************************************************     
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, see http://www.gnu.org/licenses/
//
/*****************************************************************************/
int lightPin = 2;    //connects the digital pin to the Light Detector Board's output
int ledPin = 13;     //establishes the pin to drive the LED


void setup(){      
  pinMode(lightPin, INPUT); 
  pinMode(ledPin, OUTPUT);
  digitalWrite(lightPin, LOW);
}


//to adjust the amount of light the sensor detects, adjust VR1 on the Light Detector Board
void loop()
{
     if(digitalRead(lightPin) == LOW)   // when the sensor does not detect light
     {
       digitalWrite(ledPin, LOW);   //the LED will be OFF
       delay(50);
      }         

     if(digitalRead(lightPin) == HIGH) //when the sensor detects light 
     {      
       digitalWrite(ledPin, HIGH);  //the LED will be ON
       delay(50);
      }
          }
