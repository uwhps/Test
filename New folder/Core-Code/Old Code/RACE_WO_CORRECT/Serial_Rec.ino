const int SENT_REDUNDANCY = 2;
boolean lineError = false;
String chunks[SENT_REDUNDANCY];

float getData(int pos) {
  lineError = false;
  splitChunks(readPilot(lookupChar(pos)));
  float a = parseString(chunks[0]);
  float b = parseString(chunks[1]);
  if (a!=b) 
    lineError = true;
  return a;
}

void splitChunks(String input) {
  int index = 0;
  int last = 0;
  for (int i = 0; i < input.length() && index < SENT_REDUNDANCY; i++) {
    //dumb graphics: {
    if (input.charAt(i) == '}') {
      chunks[index] = input.substring(last,i+1);
      index++;
      last = i+1;
    }
  }
}

char lookupChar(int pos) {
  return lookup[pos % INPUT_SIZE];
}  
  
boolean lineErr() {
  return lineError;
}

String readPilot(char command) {
  inputString = "";
  int start = millis();
  char inChar;
  ardupilot.print(command);
  while (inChar!= '\n' && ardupilot.available() && millis() - start <= COM_CUT) {
    inChar = (char)ardupilot.read();
    inputString = inputString + inChar;
  }
  int opensig = 0;
  int closesig = 0;
  for (int i = 0; i < inputString.length(); i++) {
    if (inputString.charAt(i) == '{')
      opensig++;
    if (inputString.charAt(i) == '}')
      closesig++;
  }
  if ((opensig < SENT_REDUNDANCY || closesig < SENT_REDUNDANCY)) {
    //Serial.println("READ ERROR: INCOMPLETE CHUNK: " + inputString);
    lineError = true;
    return ("");  
  }
  return(inputString);
}

float parseString (String input) {
  int openBracket = 0;
  int closeBracket = 0;
  int b;
  int e;
  for (int i = 0; i < input.length(); i++) {
    if (input.charAt(i) == '[') {
      openBracket++;
      b = i;
    }
    if (input.charAt(i) == ']') {
      closeBracket++;
      e = i;
    }
  }
  if (openBracket == 1 && closeBracket == 1 && b+1 < e) {
    String temp = input.substring(b+1, e);
    return toFloat(findP(temp), temp);   
  } else {
    //Serial.println("CORRUPTED DATA CHUNK");
    lineError = true;
    return (0.0);
  }  
}

int findP(String input) {
  int p = -1;
  boolean calc = true;
  for (int i = 0; i < input.length() && calc; i++) {
    if (input.charAt(i) == '.') {
      if (p < 0) {
        p=i;
        calc = false;
      } 
    }
  }
  if (p == -1) {
    //Serial.println("NO DECIMAL");
    lineError = true;
  }
  return p;
}

//assumes there is only one period and it is at p while all other characters are 0-9
float toFloat(int p, String input) {
  float a = (float)input.substring(0,p).toInt();
  float b = (float)input.substring(p+1, input.length()).toInt()/pow(10,input.substring(p+1, input.length()).length());
  if (a < 0) 
    a = a - b;
  else 
    a = a + b;
  return (a);
}

String cutChunk(String temp) {
  lineError = false;  
  int beginning = 0;
  int ending = 0;
  for (int i = 0; i < inputString.length(); i++) {
    if (inputString.charAt(i) == '{')
      beginning = i;
    if (inputString.charAt(i) == '}')
      ending = i;
  }
  if (temp.equals("") || beginning + 1 >= ending) {
    lineError = true;
    return temp;
  }
  return temp.substring(beginning + 1, ending);
}



