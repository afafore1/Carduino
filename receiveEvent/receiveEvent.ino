
const int motor1 = 12;
const int motor1B = 9;
const int motor1Speed = 3;

const int motor2 = 13;
const int motor2B = 8;
const int motor2Speed = 11;

const int block = 40;
const int block2 = 17;

const int speedRate = 150;
long x = 0; // right hand side
long y = 0; // left hand side

unsigned long startTime;
unsigned long endTime;
int braketime = 700;

#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  pinMode(motor1B, OUTPUT); // brake channel A pin
  pinMode(motor2, OUTPUT);
  pinMode(motor2B, OUTPUT);
}

void loop() {
  delay(10);
  startTime = millis();
  while(x > block && y > block){
    forward(speedRate);
  }
  if(x > block2 && y > block2){
    if(x > y){
      right(1);
    }else{
      left(1);
    }
  }else{
    brake();
    int space = 23;
    while(x < space || y < space){
      if(x > y || x == y){
        right(0);
      }else{
        left(0);
      }
    }
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  x = Wire.read();  
  y = Wire.read();    // receive byte as a long
}

void forward(int i) {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor1B, LOW);
  analogWrite(motor1Speed, i);
  Serial.println("forward");
}

void backward(int i) {
  digitalWrite(motor1, LOW);
  digitalWrite(motor1B, LOW);
  analogWrite(motor1Speed, i);
  Serial.println("backward");
}

void left(int i) {
  digitalWrite(motor2, LOW);
  digitalWrite(motor2B, LOW);
  analogWrite(motor2Speed, speedRate); 
  Serial.println("left");
  if (i > 0) {
    forward(speedRate);
  } else {
    backward(speedRate);
  }
}

void  right(int i) {
  digitalWrite(motor2, HIGH);
  digitalWrite(motor2B, LOW);
  analogWrite(motor2Speed, 255);
  Serial.println("right");
  if (i > 0) {
    forward(speedRate);
  } else {
    backward(speedRate);
  }
}

void brake() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor1B, LOW);
  analogWrite(motor1Speed, 255);
  delay(braketime);
  digitalWrite(motor1B, HIGH); // brake
  digitalWrite(motor2B, HIGH);
  Serial.println("brake");
  delay(400);
}
