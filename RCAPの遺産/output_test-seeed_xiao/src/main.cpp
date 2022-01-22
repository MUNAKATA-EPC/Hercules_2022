#include <Arduino.h>

#define echoPin1 1  //  前超音波のechoピン
#define trigPin1 2  //  前超音波のトリガー
#define echoPin2 3  //  左超音波のechoピン
#define trigPin2 4  //  左超音波のトリガー
#define echoPin3 5  //  後超音波のechoピン
#define trigPin3 6  //  後超音波のトリガー
#define echoPin4 9  //  右超音波のechoピン
#define trigPin4 10  //  右超音波のトリガー

void setup() {
  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(trigPin4, OUTPUT);
}

void loop() {
  digitalWrite(trigPin1, HIGH);
  digitalWrite(trigPin2, HIGH);
  digitalWrite(trigPin3, HIGH);
  digitalWrite(trigPin4, HIGH);
}