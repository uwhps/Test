class Fin {
private: 
  int center;
  int ll = 90;
  int ul = 0;
  int offset = 0;
  Servo thisServo;
  int truncate();
public:
  void attach();
  void center();
  void offset();
};

//attaches Servo
void Fin::attach(int pin, float center, float ll, float ul) {
  this->thisServo.attach(pin);
  this->center = center;
  this->limits = limits;
  this->ll = ll;
  this->ul = ul;
}

//allows for some offset
void Fin::offset(int offset) {
  this->offset = offset;
}

//centers the servo
void Fin::center() {
  this->thisServo.write(center);
}

//writes positions to servo
void Fin::write(int number) {
  this->thisServo.write(truncate(center + number + offset));
}

//when out of range +/- limit.  I is made to equal the extremes 
int Fin::truncate(float i) {
  if (i < ll)
    i = ll;
  else if (i > ul)
    i = ul;
  return i;
}




