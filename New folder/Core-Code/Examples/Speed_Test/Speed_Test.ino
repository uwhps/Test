const int cycles = 1000;
const int loops = 100;
unsigned long data[loops];
unsigned long starting;
unsigned long ending;
boolean run = true;

int a = 0;
int b = 1;
int c = 1;
void setup()
{
  Serial.begin(115200);
}

void loop()
{
  while(run) {
    for (int i = 0; i < loops; i++) {
      starting = micros();
      for (int j = 0; j < cycles; j++) {
        //THIS IS WHERE YOU SHOULD PUT YOU'RE CODE
        
        float a = 4.2 +36.555;
        
      }
      ending = micros();
      Serial.println();
      Serial.print("Loop number ");
      Serial.print(i);
      Serial.print(" took an average of ");
      Serial.print((ending-starting)/cycles);
      Serial.print(" microseconds per operation");
      data[i] = (ending-starting)/cycles;
    }

    //sum the array and find standard deviation
    unsigned long big = data[0];
    unsigned long little = data[0];
    unsigned long sum = 0;

    for (int i = 0; i < loops; i++) {
      sum = data[i] + sum;
      if (big < data[i]) {
        big = data[i];
      }
      if (little > data[i]) {
        little = data[i];
      }
    }
    Serial.println("\n");
    Serial.print("Total time is ");
    Serial.print(sum / loops);
    Serial.print(" microseconds with a range of +/- ");
    Serial.print(big - little);
    Serial.println();
    Serial.println();
    run = false;
  }
}

