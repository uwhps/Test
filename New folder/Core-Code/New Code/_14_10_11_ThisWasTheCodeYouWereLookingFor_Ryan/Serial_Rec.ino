const char lookup[] = {'r','p','y'};
const char ref[] = {'{','l',':','[','x',']','}'};
const char REF_SIZE = sizeof(ref)/sizeof(char);

int BUFFER_SIZE = 100;
int CHUNK_REDUNDANCY = 1;
boolean error = false;
buffer[BUFFER_SIZE];
  
boolean correct() {
  return error;
}

void printBuffer() {
  //prints buffer.  Kept for future debugging purposes
  for (int i = 0; i < BUFFER_SIZE; i++) {
    char temp = buffer[i];
    if (temp == '\n')
      Serial.print("\\n");
    else if (temp == '\0')
      Serial.print("\\0");
    else
      Serial.print(temp);
  }
  Serial.println();
}

float getData(int pos) {
  error = false;
  writeToBuffer(readPilot(lookupChar(pos)));

  String one = takeChunk();
  String two = takeChunk();
  
  if (one.equals(two)) {
    int beginning = -1;
    int ending = -1;
    for (int i = 0; i < one.length(); i++) {
      if (one.charAt(i) == '[') {
        beginning = i;
        break;
      }
    }
    for (int i = 0; i < one.length(); i++) {
      if (one.charAt(i) == ']') {
        ending = i;
        break;
      }
    }
    if (beginning > -1 && ending > beginning) {
      if (one.charAt(beginning-2) == lookupChar(pos)) {
        one = one.substring(beginning+1, ending);
        char tempBuffer[6];
        one.toCharArray(tempBuffer,6);
        return atof(tempBuffer);
      }
    }
  }
  error = true;  
  return 0.0;
}
String takeChunk() {
  int ending = -1;
  char lastChar = ref[REF_SIZE-1]
  String temp = "";
  for (int i = 0; i < BUFFER_SIZE; i++) {
    temp += buffer[i];
    if (buffer[i] == lastChar) {
      ending = i + 1;
      break;
    }
  }
  for (int i = 0; i < ending; i++) {
    buffer[i] = buffer[i + ending];
  }
  for (int i = ending; i < BUFFER_SIZE; i++) {
    buffer[i] = '\0';
  }
  return temp;
}

void writeToBuffer(String temp) {
  int j = 0;
  for (int i = 0; i < BUFFER_SIZE && j < temp.length(); i++) {
    if (buffer[i] == '\0') {
      buffer[i] = temp.charAt(j);
      j++;
    }
  }
}

String readPilot(char command) {
  //records start time in so we can bail and not hold up the program
  int start = millis();
  //requests data of the given character's type
  ardupilot.print(command);
  String temp;
  //reads in data to the buffer, bails and returns an error if it timed out
  for (int i = 0; i < BUFFER_SIZE && ardupilot.available(); i++) {
    temp += (char)ardupilot.read();
    if (millis() - start >= COM_CUT) {
      error = true;
      break;
    }
  }
  return temp;
}
char lookupChar(int pos) {
  return lookup[pos % INPUT_SIZE];
}  








