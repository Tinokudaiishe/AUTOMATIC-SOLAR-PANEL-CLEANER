#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define servo motor pins
const int servo1Pin = 8;
const int servo2Pin = 9;
const int servo3Pin = 10;
const int servo4Pin = 11;

// Define infrared sensor pin
const int irSensorPin = A0;

// Define LCD pins
const int lcdRS = 12;
const int lcdEN = 11;
const int lcdD4 = 5;
const int lcdD5 = 4;
const int lcdD6 = 3;
const int lcdD7 = 2;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
LiquidCrystal_I2C lcd(0x27, 20, 4);


void setup() {
  // Initialize servo motors
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);

  // Set all servo motors to 0 degrees angle
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);

  // Initialize infrared sensor pin as input
  pinMode(irSensorPin, INPUT);

  // Initialize LCD
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("Servo Motor Control");
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Read infrared sensor state
  int irState = digitalRead(irSensorPin);

  // Read serial input
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (irState == 0) {
      // Turn on servo motors based on input
      if (input == 'W') {
        servo1.write(90);
        lcd.setCursor(1, 1);
        lcd.print("MOVING UP");
      } else if (input == 'A') {
        servo2.write(90);
        lcd.setCursor(1, 2);
        lcd.print("MOVING LEFT");
      } else if (input == 'S') {
        servo3.write(90);
        lcd.setCursor(1, 3);
        lcd.print("MOVING DOWN");
      } else if (input == 'D') {
        servo4.write(90);
        lcd.setCursor(1, 4);
        lcd.print("MOVING RIGHT");
      }
    } else {
      // Turn off all servo motors if infrared sensor detects something
      servo1.write(0);
      servo2.write(0);
      servo3.write(0);
      servo4.write(0);
      lcd.setCursor(1, 0);
      lcd.print("Servos Off");
    }
  }
}
