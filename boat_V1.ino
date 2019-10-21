#include <Servo.h>

const int enable(6), dir_a(3), dir_b(5), rudder(9);
Servo rudder_servo;

char data = 0;

void setup() {
  // setup pins to use the DC motor
  pinMode(enable, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);

  // setup the servo
  rudder_servo.attach(rudder);
  rudder_servo.write(90);

  Serial.begin(9600);
}

void forward();
void backward();
void left();
void right();
void hold();
void straight();

void loop() {
  // Enable the H-Bridge Motor
  digitalWrite(enable, HIGH);

  // Get and respond to user commands
  if (Serial.available() > 0) {
    data = Serial.read();
    Serial.println(data);
    if (data == 'a') {
      forward();
      straight();
    } else if (data == 'c') {
      backward();
      straight();
    } else if (data == 'd') {
      forward();
      right();
    } else if (data == 'b') {
      forward();
      left();
    } else if (data == 'f') {
      backward();
      right();
    } else if (data == 'h') {
      backward();
      left();
    } else if (data == 'g') {
      hold();
    }
  }
}

// direction functions
void forward() {
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, LOW);
}

void backward() {
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, HIGH);
}

void left() {
  rudder_servo.write(45);
}

void right(){
  rudder_servo.write(135);
}

void hold(){
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, LOW);

  rudder_servo.write(90);
}

void straight() {
  rudder_servo.write(90);
}
