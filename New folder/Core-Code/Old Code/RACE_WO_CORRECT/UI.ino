void lightOn() {
  digitalWrite(UI,HIGH);
}
void lightOff() {
  digitalWrite(UI,LOW);
}
void lightBlink(int period) {
  safeDelay(period);
  lightOff();
  safeDelay(period);
  lightOn();
  Serial.println("!WTF!");
}
