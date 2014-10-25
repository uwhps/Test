//a and b are input pins
void setJoystickPins(int a, int b) {
  Pot x;
  Pot y;
  x.attach(a);
  y.attach(b);
}

//stores upper, center, and lower mechanical bounds of each potentiometer in the EEPROM, a non-volitile memory
void calibrate() {
  if (x.feelCenter)
    Serial.println("X CENTER ACCEPTED");
  if (x.feelLower)
    Serial.println("X LOWER ACCEPTED");
  if (x.feelUpper)
    Serial.println("X UPPER ACCEPTED");
  if (y.feelCenter)
    Serial.println("Y CENTER ACCEPTED");
  if (y.feelLower)
    Serial.println("Y LOWER ACCEPTED");
  if (y.feelUpper)
    Serial.println("Y UPPER ACCEPTED");
}

float getX(float a, float b) {
  return x.get(float a, float b);
}

float getY(float a, float b) {
  return y.get(float a, float b);
}

//class for potentiometer with mechanical limits to its range of motion
class Pot {
private:
  int pin;
  int center;
  int dis;
  int getRaw();

public:
  void attach();
  float get();
  boolean feelCenter();
  boolean feelDis();
  
}

Pot::Pot{
  this->int pin = 0;
  this->int dis = 511;
  this->int center = 511;
  this->LTS dis;
  this->LTS center;
}

void Pot::attach(int pin) {
  this.pin = pin;
  if (dis.claim(float.sizeOf()))
    dis = dis.read();
  else
    Serial.println("EEPROM CANNOT BE CLAIMED FOR DIPLACEMENT READING");
  if (center.claim(float.sizeOf()))
    center = center.read();
  else
    Serial.println("EEPROM CANNOT BE CLAIMED FOR CENTER READING");
}

int Pot::getRaw() {
  return analogRead(pin);
}

//assumes a < b for speed considerations
float Pot::get(float a, float b){
  return tmap(getRaw(),ll, ul, a, b);
}

//note: a lookup table was not implemented to save memory space on the board
boolean Pot::feelCenter() {
  return(LTS.write(CENTER_LOC, getRaw()));
}
boolean Pot::feelDis() {
  if (Serial) {
    int store = this.getRaw();
    int temp;
    while (Serial.read() != 'o') {
      temp = this.getRaw();
      if (temp > store)
        store = temp;
    }   
    int storen = this.getRaw();;
    while (Serial.read() != 'o') {
      temp = this.getRaw();
      if (temp < storen)
        storen = temp;
    }
    if (store - center > center - storen) 
      return (dis.write(store - center));
    else
      return (dis.write(center - storen));
  }
  return false;
}




