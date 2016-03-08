// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.
const int motor1 = 12;
const int motor1B = 9;
const int motor1Speed = 3;

const int motor2 = 13;
const int motor2B = 8;
const int motor2Speed = 11;

const int block = 40;
const int block2 = 11;

const int speedRate = 125;
long x = 0; // right hand side
long y = 0; // left hand side

#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  pinMode(motor1, OUTPUT);
  pinMode(motor1B, OUTPUT); // brake channel A pin
  pinMode(motor2, OUTPUT);
  pinMode(motor2B, OUTPUT);
}

void loop() {
  delay(10);
  if (x > block || y > block) {
    if(x > block && y > block){
      forward(speedRate);
    }
    else if( x > y){
      left(1);
    }else
      right(1);
  } 
  else if (x != 0 && x < block2 || y != 0 && y < block2) {
    brake();
    while (x < block || y < block) {
      if(x > y){
        left(0);
      }else{
        right(0);
      }
    }
  } else if (x == 0 && y == 0) {
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  //while (1 < Wire.available()) {
  x = Wire.read();
  Serial.print("x is ");
  Serial.println(x);
  //}
  
  y = Wire.read();    // receive byte as a long
  Serial.print("y is ");
  Serial.println(y);         // print the integer
}

void backward(int i) {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor1B, LOW);
  analogWrite(motor1Speed, i);
  Serial.println("backward");
}

void forward(int i) {
  digitalWrite(motor1, LOW);
  digitalWrite(motor1B, LOW);
  analogWrite(motor1Speed, i);
  Serial.println("forward");
}

void left(int i) {
  digitalWrite(motor2, LOW);
  digitalWrite(motor2B, LOW);
  analogWrite(motor2Speed, 255); //run at half speed
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
  digitalWrite(motor1B, HIGH); // brake
  digitalWrite(motor2B, HIGH);
  Serial.println("brake");
  delay(100);
}
