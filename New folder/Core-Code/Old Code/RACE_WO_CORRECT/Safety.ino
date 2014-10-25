 

void prepLowError(int a) {
  pinMode(a ,OUTPUT);
  digitalWrite(a ,HIGH);
}

//instead of delaying program execution, this function will hold the execution but still determine if things are safe to continue
void safeDelay(int del) {
  long int finish = millis()+(del);    
  while (safe() && (finish > millis())) {    
  }  
}

void shutdown() {
  Serial.println("Shutting Down");
  digitalWrite(RELAY,LOW);
  while(true){}
}

void emergencyShutdown() {
  digitalWrite(RELAY,LOW);
  Serial.println("Water Detected!");
  while(true){}
}

boolean safe () {
  int waterLevel = analogRead(WATER_PIN);
  //Serial.println(waterLevel);
  if (waterLevel > WATER) {
    return(true);
  } else {
    emergencyShutdown();
    return(false);
  }
}
