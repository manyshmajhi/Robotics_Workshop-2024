const int trigger = 7;
const int echo = 6;
const int RED = 13;
const int GREEN = 12;

int duration;
int distance;

void setup() {
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigger, LOW);
  delay(10);
  digitalWrite(trigger, HIGH);
  delay(100);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH);
  distance = 0.0340 * duration / 2;
  //Serial.println(distance);                 //this line is for debugging purpose

  if(distance < 20) {
    digitalWrite(RED, HIGH);
    delay(1000);
    digitalWrite(GREEN, LOW);
    delay(1000);
  }
  else {
    digitalWrite(GREEN, HIGH);
    delay(1000);
    digitalWrite(RED, LOW);
    delay(1000);
  }
}
