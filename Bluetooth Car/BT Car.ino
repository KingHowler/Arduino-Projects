#include <SoftwareSerial.h> //library for software serial
#include "L298N_Car.h"
SoftwareSerial bt(6, 7);// (Change these as required!)

char data_in; // data received from serial link
int speed = 150;


// Motor Connections
const int LF = A0;     // Left Forward
const int LS = A1;     // Left Speed
const int LB = A2;     // Left Backward
const int RF = A3;     // Right Forward
const int RS = A5;     // Right Speed
const int RB = A4;     // Right Backward

//LED Lights
const int RLED = 2; // Right Signal
const int LLED = 3; // Left Signal
const int HLED = 4; // Head Light
const int BLED = 5; // Back Light

void setup() {
  bt.begin(9600); // Change baud rate as required!
  Start_Car();
}

void loop() {
  if (bt.available()){            // If Data is received
    data_in=bt.read();            // Store the data in a container

    if(data_in=='R'){             // If data is 'R'
      right(speed, speed);        // Turn right
    }
    if(data_in=='L'){             // If data is 'L'
      left(speed, speed);         // Turn left
    }
    if(data_in=='F') {            // If data is 'F'
      forward(speed, speed);      // Go Forward
    }
    if(data_in=='B') {            // If data is 'B'
      backward(speed, speed);     // Go Backward
    }
    if(data_in=='0') {            // If data is '0'
      stop();                     // Stop
    }
    if(data_in=='H') {            // If data is 'H'
      digitalWrite(HLED, HIGH);   // Turn Headlights on
    }
    if(data_in=='h') {            // If data is 'h'
      digitalWrite(HLED, LOW);    // Turn Headlights off
    }
    if(data_in=='X') {            // If data is 'X'
      speed = 255;                // Set Speed to 255
    }
    if(data_in=='x') {            // If data is 'x'
      speed = 150;                // Set Speed to 150
    }
    if(data_in=='S') {            // If data is 'S'
      speed = 0;                  // Set Speed to 0
    }
  }
}

void Start_Car() {
  pinMode(LF , OUTPUT);
  pinMode(LB , OUTPUT);
  pinMode(LS , OUTPUT);
  pinMode(RF , OUTPUT);
  pinMode(RB , OUTPUT);
  pinMode(RS , OUTPUT);
  analogWrite(LS, 0);
  analogWrite(RS, 0);
  digitalWrite(LF , LOW);
  digitalWrite(LB , LOW);
  digitalWrite(RF , LOW);
  digitalWrite(RB , LOW);
  digitalWrite(RLED , LOW);
  digitalWrite(LLED , LOW);
  digitalWrite(HLED , LOW);
  digitalWrite(BLED , LOW);
}

void forward(int L_Speed, int R_Speed) {
  analogWrite(LS, L_Speed);
  analogWrite(RS, R_Speed);
  digitalWrite(LF , HIGH);
  digitalWrite(LB , LOW);
  digitalWrite(RF , HIGH);
  digitalWrite(RB , LOW);
}

void backward(int L_Speed, int R_Speed) {
  analogWrite(LS, L_Speed);
  analogWrite(RS, R_Speed);
  digitalWrite(LF , LOW);
  digitalWrite(LB , HIGH);
  digitalWrite(RF , LOW);
  digitalWrite(RB , HIGH);
  digitalWrite(BLED , HIGH);
}

void left(int L_Speed, int R_Speed) {
  analogWrite(LS, L_Speed);
  analogWrite(RS, R_Speed);
  digitalWrite(LF , LOW);
  digitalWrite(LB , HIGH);
  digitalWrite(RF , HIGH);
  digitalWrite(RB , LOW);
  digitalWrite(LLED , HIGH);
}

void right(int L_Speed, int R_Speed) {
  analogWrite(LS, L_Speed);
  analogWrite(RS, R_Speed);
  digitalWrite(LF , HIGH);
  digitalWrite(LB , LOW);
  digitalWrite(RF , LOW);
  digitalWrite(RB , HIGH);
  digitalWrite(RLED , HIGH);
}

void stop() {
  analogWrite(LS, 0);
  analogWrite(RS, 0);
  digitalWrite(LF , LOW);
  digitalWrite(LB , LOW);
  digitalWrite(RF , LOW);
  digitalWrite(RB , LOW);
  digitalWrite(RLED , LOW);
  digitalWrite(LLED , LOW);
  digitalWrite(BLED , LOW);
}