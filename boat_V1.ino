#include <Servo.h>

const int enable(6), dir_a(3), dir_b(5), rudder(9);
Servo rudder_servo;

char data = 0;

const int green_led(10), blue_led(11), red_led(12), yellow_led(13);

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

  // reset all LEDs
  digitalWrite(green_led, LOW);
  digitalWrite(blue_led, LOW);
  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, LOW);

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

  digitalWrite(green_led, HIGH);
  digitalWrite(red_led, LOW);
}

void backward() {
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, HIGH);

  digitalWrite(red_led, HIGH);
  digitalWrite(green_led, LOW);
}

void left() {
  rudder_servo.write(45);

  digitalWrite(yellow_led, HIGH);
  digitalWrite(blue_led, LOW);
}

void right(){
  rudder_servo.write(135);

  digitalWrite(blue_led, HIGH);
  digitalWrite(yellow_led, LOW);
}

void hold(){
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, LOW);

  rudder_servo.write(90);

  digitalWrite(green_led, LOW);
  digitalWrite(blue_led, LOW);
  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, LOW);
}

void straight() {
  rudder_servo.write(90);

  digitalWrite(yellow_led, LOW);
  digitalWrite(blue_led, LOW);
}
