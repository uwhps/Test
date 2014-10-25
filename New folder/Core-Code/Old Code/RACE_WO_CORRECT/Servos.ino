void writeServos(int top, int bottom,int left,int right) {
  topServo   .write(SERVO_CENTER + top    );
  bottomServo.write(SERVO_CENTER + bottom );
  leftServo  .write(SERVO_CENTER + left   );
  rightServo .write(SERVO_CENTER + right  );
}

void centerServos() {
  writeServos(0,0,0,0);
}

int truncate(int i, int limit) {
  if (i < -limit)
    i = -limit;
  else if (i > limit)
    i = limit;
  return i;
}

