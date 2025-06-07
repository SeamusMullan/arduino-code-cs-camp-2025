// Automatic Plant Watering Alert
// This project uses a water sensor in the soil to check if your plant needs water.
// If the soil is dry, it lights up an LED and prints a message.
//
// Connect the water sensor:
// - VCC to 5V
// - GND to GND
// - Signal to D2
//
// Connect an LED (with resistor) to D8.

const int soilSensorPin = 2; // Digital pin for water sensor
const int ledPin = 8;        // LED pin

void setup() {
  pinMode(soilSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Plant Watering Alert Ready");
}

void loop() {
  int soilWet = digitalRead(soilSensorPin);
  if (soilWet == LOW) {
    digitalWrite(ledPin, HIGH); // Soil is dry, turn on LED
    Serial.println("Soil is dry! Please water your plant.");
  } else {
    digitalWrite(ledPin, LOW); // Soil is wet, turn off LED
    Serial.println("Soil is wet. No need to water.");
  }
  delay(2000);
}
