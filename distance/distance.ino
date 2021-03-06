#include <Wire.h>

const int trigPin1 = 2;
const int echoPin1 = 4;
const int trigPin2 = 8;
const int echoPin2 = 9;
long duration1, inches1, cm1, duration2, inches2, cm2;
long x = 0; 
long y = 0;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop(){
  Wire.beginTransmission(8);
  x = calcDist1();
  delay(10);
  y = calcDist2();
  delay(10);
  Wire.write(x);
  Wire.write(y);
  Wire.endTransmission();
  delay(10);
}

long calcDist2(){
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);

  inches2 = microsecondsToinches(duration2);
  cm2 = microsecondsTocm(duration2);
  return inches2;

}
long calcDist1(){
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);

  inches1 = microsecondsToinches(duration1);
  cm1 = microsecondsTocm(duration1);
  
  return inches1;
}
long microsecondsToinches(long microseconds){
  return microseconds / 74 / 2;
}

long microsecondsTocm(long microseconds){
  return microseconds / 29 / 2;
}

