/*
 * Code made for the Centre D'art Contemporain in Geneva by e-garbage
 * Code addapted from the ServoEasing libraray example Simple.cpp file.
 * Library by Armin Joachimsmeyer
 * Check https://github.com/ArminJo/ServoEasing for more infos
 * Tested on arduino Nano Only, but the code should work on other platform to
 */

#include <Arduino.h>
#include "ServoEasing.hpp"
#include "PinDefinitionAndMore.h"

/*
 * Pin mapping table for different platforms - used by all examples
 *
 * Platform         Servo1      Servo2      Servo3      Analog     Core/Pin schema
 * -------------------------------------------------------------------------------
 * (Mega)AVR + SAMD    9          10          11          A0
 * ATtiny3217         20|PA3       0|PA4       1|PA5       2|PA6   MegaTinyCore
 * ESP8266            14|D5       12|D6       13|D7        0
 * ESP32               5          18          19          A0
 * BluePill          PB7         PB8         PB9         PA0
 * APOLLO3            11          12          13          A3
 * RP2040             6|GPIO18     7|GPIO19    8|GPIO20
 */

ServoEasing Servo1;

// CHANGE VALUES BELOW TO ADJUST TO DESIRED MOVEMENT 

const int StartPos= 70; //80 this value determine the neutral position for the pendulum
const int Amplitude= 7; // 15 Movement half amplitude 
const int MoveSpeed= 85; // 30 Speed :) increase speed for louder clicking sound
const int TypeOfEasing=0; // Set the type of Easing 0=Linear Easing, 1=Quadratic, 2= Cubic
const int MoveStopTime=1200; //500 Waiting time between each movements, Longer time give more stable comportement



void setup() {
    Serial.begin(9600);
    Serial.println(F("[-] START " __FILE__ " from " __DATE__ "\r\n[-] Using library version " VERSION_SERVO_EASING));
    Serial.println(F("[+] Attach servo at pin " STR(SERVO1_PIN)));
    Servo1.attach(SERVO1_PIN, StartPos);
    delay(8000);
    Serial.println(F("[+] Init Position"));
    if (TypeOfEasing==0)
    {
      Servo1.setEasingType(EASE_LINEAR);
      Serial.println(F("Linear ease"));
    }
    else if (TypeOfEasing==1)
    {
      Servo1.setEasingType(EASE_QUADRATIC_IN_OUT);
      Serial.println(F("quadratic ease"));
    }
    else if (TypeOfEasing==2)
    {
      Servo1.setEasingType(EASE_CUBIC_IN_OUT);
      Serial.println(F("Cubic ease"));
    }
    else
    {
      Serial.println(F("TypeOfEasing variable out of range value. It only accept 0=Linear Easing, 1=Quadratic, 2= Cubic"));
    }
}

void loop() {
    char buffer [255];
    char buffer2 [255];
    int MovePositive = (StartPos+Amplitude);
    int MoveNegative = (StartPos-Amplitude);
    sprintf(buffer, "Move to position %d at speed %d degree per sec", MovePositive, MoveSpeed);
    Serial.println(buffer);
    Servo1.easeTo(MovePositive,MoveSpeed);
    delay(MoveStopTime);
    sprintf(buffer2, "Move to position %d at speed %d degree per sec", MoveNegative, MoveSpeed);
    Serial.println(buffer2);
    Servo1.easeTo(MoveNegative,MoveSpeed);
    delay(MoveStopTime);
}