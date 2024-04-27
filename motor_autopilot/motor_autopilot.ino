const int echo = 6;
const int trig = 7;
const int IN1=8;
const int IN2=9;
const int IN3=10;
const int IN4=11;
// const int greenLED = 12;
// const int redLED = 13;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);
}

void turRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);
}

void release() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, LOW);
}

int duration;
float speed = 0.0340;

void sendPulse() {
  digitalWrite(trig, LOW);
  delay(10);
  digitalWrite(trig, HIGH);
  delay(100);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
}

int calculateDistanceInCM() {
  return (speed*duration)/2;
}

int scanRight() {
  turnRight();
  sendPulse();
  if(calculateDistanceInCM() < 30) {
    return 1;
  }
  else {
    return 0;
  }
}

int scanLeft() {
  turnLeft();
  sendPulse();
  if(calculateDistanceInCM() < 30) {
    return 1;
  }
  else {
    return 0;
  }
}

char data;
int obstacleDistance;

void loop() {
  sendPulse();
  obstacleDistance = calculateDistanceInCM();

  if(obstacleDistance < 30) {
    if(scanRight() == 1) {
      if(scanLeft() == 0) {
        turnLeft();
      }
      else {
        release();
      }
    }
    else {
      turnRight();
    }
  }
  else {
    forward();
  }
}