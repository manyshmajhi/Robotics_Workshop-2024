int ENA = 6;
int ENB = 7;
const int leftIR = 12;
const int rightIR = 13;

void setup() {
  analogWrite(ENA, 127);
  analogWrite(ENB, 127);
  pinMode(rightIR, INPUT);
  pinMode(leftIR, INPUT);
  Serial.begin(9600);
}

const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void release() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveLeftWheel() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveRightWheel() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

int rightIRdata;
int leftIRdata;

void loop() {
  rightIRdata  = digitalRead(rightIR);
  Serial.print("rightIRdata : "); Serial.println(rightIRdata );
  leftIRdata  = digitalRead(leftIR);
  Serial.print("leftIRdata : "); Serial.println(leftIRdata );

  if (rightIRdata == 0 && leftIRdata == 0) {
    moveForward();
  }
  else if(rightIRdata == 1 && leftIRdata == 1) {
    release();
  }
  else if(rightIRdata == 1 && leftIRdata == 0) {
    moveLeftWheel();
  }
  else if(rightIRdata == 0 && leftIRdata == 1) {
    moveRightWheel();
  }
}
