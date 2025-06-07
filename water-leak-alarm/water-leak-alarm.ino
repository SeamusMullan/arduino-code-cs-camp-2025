// Water Leak Alarm
// This project uses a water sensor to detect leaks and sounds an alarm (buzzer or LED).
//
// Connect the water sensor:
// - VCC to 5V
// - GND to GND
// - Signal to D2
//
// Connect a buzzer or LED (with resistor) to D8.

const int waterSensorPin = 2; // Digital pin for water sensor
const int alarmPin = 8;       // Pin for buzzer or LED

void setup() {
  pinMode(waterSensorPin, INPUT);
  pinMode(alarmPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Water Leak Alarm Ready");
}

void loop() {
  int waterDetected = digitalRead(waterSensorPin);
  if (waterDetected == HIGH) {
    digitalWrite(alarmPin, HIGH); // Turn on alarm
    Serial.println("WATER DETECTED! Alarm ON");
  } else {
    digitalWrite(alarmPin, LOW); // Turn off alarm
    Serial.println("No water detected.");
  }
  delay(500);
}
