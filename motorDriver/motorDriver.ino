const int IN1=8;  //green
const int IN2=9;  //blue
const int IN3=10; //purple
const int IN4=11; //white

void setup() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  Serial.begin(9600);
}

char data;

void loop() {
  if (Serial.available()>0){
    data=Serial.read();
    Serial.println(data);

    switch(data) {
      case 'y':
        //up button
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN4,LOW);
        digitalWrite(IN3,HIGH);
        break;
      case 'a':
        //down button
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN4,HIGH);
        digitalWrite(IN3,LOW);
        break;
      case 'b':
        //right button
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN4,LOW);
        digitalWrite(IN3,LOW);
        break;
      case 'x':
        //left button
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,LOW);
        digitalWrite(IN4,LOW);
        digitalWrite(IN3,HIGH);
        break;
      case 'z':
        //released
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,LOW);
        digitalWrite(IN4,LOW);
        digitalWrite(IN3,LOW);
        break;
    }
  }
}
