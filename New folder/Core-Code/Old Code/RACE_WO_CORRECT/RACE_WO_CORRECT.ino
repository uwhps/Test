#include <Servo.h>
#include <SoftwareSerial.h>
#include <Button.h>
#include <EEPROM.h>

Button Pitch;
Button Brakes;
Button Start;
Button Stop;

Servo topServo;
Servo bottomServo;
Servo leftServo;
Servo rightServo;
const int SERVO_CENTER = 90;
int top,bottom,left,right;
const signed int DEGREE = 30;

const int WATER = 800;
const int WATER_PIN = 2;
const int RELAY = 2;

const int UI = 13;

const int COM_CUT = 50;
long int fail = 0;
long int success = 0;
const int UPDATE_PERIOD = 10;
int lastUpdate = 0;

int executionCycle = 0;

//RX, TX
SoftwareSerial ardupilot(11,12);

const int DEGREE_ERROR = 10;
const char lookup[] = {'r','p','y'};
const int INPUT_SIZE = sizeof(lookup)/sizeof(char);
const int REDUNDANCY = 4;
float data[INPUT_SIZE][REDUNDANCY];
float initials[INPUT_SIZE];
boolean newData = false;

const int deltaJoystick = 6;
unsigned long lastPrint;

String inputString;
void setup() { 
  prepLowError(RELAY);
   
  if (safe()) {
    Serial.begin(115200);
    ardupilot.begin(28800);
    topServo    .attach(10);
    bottomServo .attach(9 );
    leftServo   .attach(6 );
    rightServo  .attach(5 );
    
    Pitch        .attach(7 );
    Brakes      .attach(4 );
    Start       .attach(A4);
    Stop        .attach(A5); 
    pinMode(UI, OUTPUT); 

    readButtons();
    while (safe() && Start.isDown()){
      lightBlink(50);
      readButtons();
    }
  
    Serial.println("!Centering!");
    centerServos();
    safeDelay(1000);
    setJoystickPins(1,0);
    safeDelay(20);
    
    boolean spool = true;
    while (safe() && spool) {
      Serial.println("spooling");
      safeDelay(20);
      String temp = cutChunk(readPilot('o'));
      Serial.println(temp);
      if (temp.equals("YES")) {
        spool = false;
      }
    } 
    do {
      updateData();
      lastUpdate = 0;
    } while (lineErr() && safe());
    lightOn();
    Serial.println("!Start!");
  }
}

void loop() {   
  while (safe()) {
    setZero();
    //updateData();
    readButtons();    
    if (Stop.isDown()) {
      shutdown();
    }
    /*
    if (Pitch.isDown()) {
      float a = data[1][0]/5;
      if (a > DEGREE) 
        a = DEGREE;
      if (a < DEGREE)
        a = -DEGREE;
      if (abs(a) >=1)
        a = 0;  
      joystickAdjust(getX(), a); 
    } else {
      joystickAdjust(getX(), getY()); 
    }
    */
    joystickAdjust(getX(), getY());
    while (safe() && Start.isDown()){
      lightBlink(50);
      readButtons();
    }
    if (Brakes.isDown()) {
      top = DEGREE;
      bottom = DEGREE;
      right = -DEGREE;
      left = -DEGREE;
      Serial.print("BRAKES");
    }
    writeServos(top,bottom,left,right);
    if (millis()-lastPrint >= 1000) {
      printAll();
      lastPrint = millis();
    }
    executionCycle++;
  }
  
}
void updateData() {
  if (lastUpdate == 0) {
    float a = getData(1);
    if (lineErr()) {
      fail++;
    } else {
      success++;
      for (int i = 1; i<REDUNDANCY; i++) {
        data[1][i] = data[1][i-1];
      }
      data[1][0] = a;
      newData = true;
    }
  }
  lastUpdate++;
  if (lastUpdate == UPDATE_PERIOD) {
    lastUpdate = 0;
  }
}

void setZero() {
  top = 0;
  bottom = 0;
  left = 0;
  right = 0;
}

void joystickAdjust (int a, int b) {
  if (abs(a) >= deltaJoystick) {
    top = a;
    bottom = -a;
  }
  if (abs(b) >= deltaJoystick) {
    left = -b;    
    right = b;
  }
}

void readButtons() {
  Brakes   .readState();
  Stop      .readState();
  Start     .readState();
  Pitch  .readState();
}

void printAll () {
  if (!Serial.available()) {
    Serial.print("<jx:");
    Serial.print(getX());
    Serial.print("  jy:");
    Serial.print(getY());
    
    Serial.print("  r:");
    Serial.print(data[0][0]);
    Serial.print("  p:");
    Serial.print(data[1][0]);
    Serial.print("  y:");
    Serial.print(data[2][0]);
    
    Serial.print("  Buttons:");
    Serial.print(Stop   .isDown());
    Serial.print(Brakes .isDown());
    Serial.print(Pitch.isDown());
    Serial.print(Start  .isDown());
    
    Serial.print("  t:");
    Serial.print(top);
    Serial.print("  b:");
    Serial.print(bottom);
    Serial.print("  l:");
    Serial.print(left);
    Serial.print("  r:");
    Serial.print(right);
    
    Serial.print(" ex:");
    Serial.print((float)executionCycle/((float)(millis()-lastPrint)/1000));
    
    Serial.print(" sf:");
    Serial.print(((float)success)/((float)(success+fail)));
    Serial.println(">");
    executionCycle = 0;
    
    if (((float)success)/((float)(success+fail)) < .6) {
      ardupilot.print('f');
    } 
    success = 0;
    fail = 0;
  }
}

