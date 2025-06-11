// Traffic Light Controller
// This project simulates a traffic light system with red, yellow, and green LEDs.
// The lights cycle through the standard traffic light sequence.
//
// Connect LEDs (with resistors) to:
// - Red LED to pin 8
// - Yellow LED to pin 9  
// - Green LED to pin 10
//
// Each LED should have a 220-ohm resistor in series.

const int redPin = 8;     // Red LED pin
const int yellowPin = 9;  // Yellow LED pin  
const int greenPin = 10;  // Green LED pin

// Timing for each phase (in milliseconds)
const int greenTime = 5000;   // 5 seconds
const int yellowTime = 2000;  // 2 seconds
const int redTime = 5000;     // 5 seconds

void setup() {
  // Initialize LED pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Traffic Light Controller Started");
  
  // Start with red light on
  allLightsOff();
  digitalWrite(redPin, HIGH);
}

void loop() {
  // Red light phase
  Serial.println("RED - Stop");
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  delay(redTime);
  
  // Green light phase
  Serial.println("GREEN - Go");
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, HIGH);
  delay(greenTime);
  
  // Yellow light phase
  Serial.println("YELLOW - Caution");
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, LOW);
  delay(yellowTime);
}

void allLightsOff() {
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
}
