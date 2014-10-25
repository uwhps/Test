/*
  Button.h - Library for reading and using Buttons.
  Created by Ryan C. Pennell, March 29, 2014.
  Released into the public domain.
*/
#ifndef Button_h
#define Button_h

#include "Arduino.h"
class Button {
private:
  int pin;
  unsigned long downAt;
  boolean down;
  boolean last;
  
public:
  Button();
  boolean isDown();
  void readState();
  unsigned long lastChange();
  void attach(int);
};
#endif