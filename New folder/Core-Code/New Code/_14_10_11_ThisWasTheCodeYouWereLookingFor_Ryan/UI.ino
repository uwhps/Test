class Light {
private:
  int pin;
}

void Light::attach(int pin) {
  this->pin = pin;

//turns light on
void Light::on() {
  digitalWrite(pin, HIGH);
}

//turns light off
void Light::off() {
  digitalWrite(pin,LOW);
}

//blinks light through one iteration and delayed safely
void lightBlink(int period) {
  safeDelay(period);
  this->off(0);
  safeDelay(period);
  this->on();
}
