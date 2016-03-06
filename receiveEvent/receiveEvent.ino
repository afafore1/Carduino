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

const int block = 36;
const int block2 = 12;

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
  delay(100);
  if(x > block && y > block){
    forward(speedRate);
    Serial.print("x = ");
    Serial.println(x);
    Serial.print("y = ");
    Serial.println(y);
  }else 
  if( y < block && y > block2){
    right(1);
    //forward();
    Serial.print("y = ");
    Serial.println(y);
  }
  else 
  if( x < block && x > block2){
    left(1);
    //forward();
    Serial.print("x = ");
    Serial.println(x);
  }else 
  if(x > 0 && x < block2 || y > 0 && y < 5){
    brake();
    if(x > 0 && x < 5){
      right(0);
      //backward();
    }else{
      left(0);
      //backward();
    }
  }else if(x == 0 && y == 0){           
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
  Serial.print("y is ");
  y = Wire.read();    // receive byte as a long
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
  if(i > 0){
    forward(speedRate);
  }else{
    backward(speedRate);
  }
}

void  right(int i) {
  digitalWrite(motor2, HIGH);
  digitalWrite(motor2B, LOW);
  analogWrite(motor2Speed, 255);
  Serial.println("right");
  if(i > 0){
    forward(speedRate);
  }else{
    backward(speedRate);
  }
}

void brake() {
  digitalWrite(motor1B, HIGH); // brake
  digitalWrite(motor2B, HIGH);
  Serial.println("brake");
  delay(100);
}
