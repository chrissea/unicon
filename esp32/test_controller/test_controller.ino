int x0[9] = {0, 0, 0, 0, 0, 0, 0, 0, 1};
int x1[9] = {0, 0, 0, 0, 0, 0, 0, 1, 1};

void setup() { 
  pinMode(15, OUTPUT);
}

void loop() {

  for ( int i = 0; i < 8; i++) {
    digitalWrite(15, 0);
    delayMicroseconds(1);
    digitalWrite(15, x0[i]);
    delayMicroseconds(1);
    digitalWrite(15, x0[i]);
    delayMicroseconds(1);
    digitalWrite(15, 1);
    delayMicroseconds(1);
  }
  delayMicroseconds(1800);

  for ( int i = 0; i < 8; i++) {
    digitalWrite(15, 0);
    delayMicroseconds(1);
    digitalWrite(15, x1[i]);
    delayMicroseconds(1);
    digitalWrite(15, x1[i]);
    delayMicroseconds(1);
    digitalWrite(15, 1);
    delayMicroseconds(1);
  }
  
  delayMicroseconds(5000);
}
