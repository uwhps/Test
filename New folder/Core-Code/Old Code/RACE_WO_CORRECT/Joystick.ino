int x_pin;
int y_pin;

const signed int CONSTRAIN = 350;
signed int X_CENTER;
signed int Y_CENTER;

//a and b are input pins
void setJoystickPins(int a, int b) {
  x_pin = a;
  y_pin = b;
  X_CENTER = EEPROM.read(0)*4;
  Y_CENTER = EEPROM.read(1)*4;
}

void feelTheStick() {
  EEPROM.write(0, getRawX()/4);
  EEPROM.write(1, getRawY()/4);
  X_CENTER = EEPROM.read(0)*4;
  Y_CENTER = EEPROM.read(1)*4;
}  

float getRawX() {
  return analogRead(x_pin);
}
  
float getRawY() {
  return analogRead(y_pin);
}

float getX() {
  int temp = getRawX() - X_CENTER;
  if (temp < -CONSTRAIN) {
    temp = -CONSTRAIN;
  } else if (temp > CONSTRAIN) {
    temp = CONSTRAIN;
  }
  return map(temp, -CONSTRAIN, CONSTRAIN, -DEGREE, DEGREE);
}
  
float getY() {
  int temp = getRawY() - Y_CENTER;
  if (temp < -CONSTRAIN) {
    temp = -CONSTRAIN;
  } else if (temp > CONSTRAIN) {
    temp = CONSTRAIN;
  }
  return map(temp, -CONSTRAIN, CONSTRAIN, -DEGREE, DEGREE);
}

