// DC Motor Speed Controller
// This project controls the speed of a DC motor using a potentiometer and PWM.
// It includes an H-bridge (L293D) for motor control and displays speed on LCD.
//
// Wiring:
// Potentiometer (10kΩ):
// - Left pin to GND
// - Middle pin (wiper) to A0
// - Right pin to 5V
//
// L293D H-Bridge:
// - Pin 1 (Enable 1,2) to pin 3 (PWM pin)
// - Pin 2 (Input 1) to pin 5
// - Pin 7 (Input 2) to pin 6
// - Pin 8 (VCC) to 5V
// - Pin 16 (VS) to external power (6-9V)
// - Pins 4,5,12,13 to GND
//
// DC Motor:
// - Connect to pins 3 and 6 of L293D (Output 1,2)
//
// LCD (16x2 with parallel interface):
// - RS to pin 8, Enable to pin 9
// - D4-D7 to pins 4,5,6,7

#include <LiquidCrystal.h>

// Initialize LCD
LiquidCrystal lcd(8, 9, 4, 11, 12, 13);

// Pin definitions
const int potPin = A0;        // Potentiometer pin
const int motorEnablePin = 3; // L293D Enable pin (PWM)
const int motorPin1 = 10;     // L293D Input 1
const int motorPin2 = 7;      // L293D Input 2

// Variables
int potValue = 0;
int motorSpeed = 0;
int speedPercent = 0;
bool motorDirection = true;   // true = forward, false = reverse

void setup() {
  // Initialize motor control pins
  pinMode(motorEnablePin, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  
  // Set initial motor direction (forward)
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Motor Controller");
  lcd.setCursor(0, 1);
  lcd.print("Speed: 0%");
  
  Serial.begin(9600);
  Serial.println("DC Motor Speed Controller Ready");
  
  delay(1000);
}

void loop() {
  // Read potentiometer value (0-1023)
  potValue = analogRead(potPin);
  
  // Map potentiometer value to motor speed (0-255 for PWM)
  motorSpeed = map(potValue, 0, 1023, 0, 255);
  
  // Calculate speed percentage for display
  speedPercent = map(potValue, 0, 1023, 0, 100);
  
  // Set motor speed using PWM
  analogWrite(motorEnablePin, motorSpeed);
  
  // Update LCD display
  lcd.setCursor(0, 1);
  lcd.print("Speed: ");
  if (speedPercent < 10) {
    lcd.print("  ");
  } else if (speedPercent < 100) {
    lcd.print(" ");
  }
  lcd.print(speedPercent);
  lcd.print("%");
  
  // Display direction
  lcd.setCursor(10, 1);
  if (motorDirection) {
    lcd.print(" FWD");
  } else {
    lcd.print(" REV");
  }
  
  // Print to serial monitor
  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print(" | Speed: ");
  Serial.print(speedPercent);
  Serial.print("% | PWM: ");
  Serial.print(motorSpeed);
  Serial.print(" | Dir: ");
  Serial.println(motorDirection ? "Forward" : "Reverse");
  
  delay(100); // Small delay for stability
}

// Optional function to change motor direction
void changeDirection() {
  motorDirection = !motorDirection;
  
  if (motorDirection) {
    // Forward
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  } else {
    // Reverse  
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
  }
}
