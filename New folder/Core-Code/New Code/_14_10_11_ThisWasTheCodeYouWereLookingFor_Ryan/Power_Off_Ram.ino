//long term storage library - extends EEPROM library
//very limited write lifetime!
#include <EEPROM.h>

class LTS {
private:
  static int pos;
  int myPos;
  int bytes;
public: 
  boolean claim();
  boolean write();
  float read();
  int read();  
};

LTS::LTS {
  static int pos;
  this->int myPos;
  this->int bytes;
}

boolean LTS::claim() {
  if (pos < 512) {
    myPosStart = pos;
    bytes = 1;
    pos++;
    return true;
  }
  return false;
}
boolean LTS::claim(int bytes) {
  if (pos + bytes <= 512) {
    myPosStart = pos;
    this.bytes = bytes;
    pos = pos + bytes;
    return true;
  }
  return false;
}
boolean LTS::write(byte mybyte) {
  EEPROM.write(mypos, mybyte);
  return true;
}
boolean LTS::write(byte[] mybyte) {
  int len = mybyte.sizeOf();
  if (len <= bytes) {
    for (int i = 0; i < len; i++) {
      EEPROM.write(mypos + i, mybyte[i]);
    }
    return true;
  }
  return false;
}
boolean LTS::write(float myfloat, int a) {
  /*
  void sendDouble(float number)
  {
    byte x[8] = {
      0,0,0,0, 0,0,0,0      };
  
    float2DoublePacked(number, x);
    // simple dump, no handshake or packetizing
    for (int i=0; i<8;i++)
      Serial.write(x[i]);
  }
  */
  return (write((byte*) &myfloat));
}  
boolean LTS::write(int myint) {
  return (write((byte*) &myint));
} 
float LTS::read() {
  if (bytes >= float.sizeOf())
    return ((float) {EEPROM.read(mypos+0),EEPROM.read(mypos+1),EEPROM.read(mypos+2),EEPROM.read(mypos+3)});
  return nan;
}
int LTS::read() {
  if (bytes >= int.sizeOf())
    return ((int) {EEPROM.read(mypos+0),EEPROM.read(mypos+1)});
  return nan;
}







