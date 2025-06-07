// Temperature-Activated Fan (or LED)
// This project turns on a fan (or LED) when the temperature is too high.
//
// Connect your temperature sensor (like TMP36) to A0.
// Connect a fan or LED (with resistor or transistor if needed) to D8.
//
// - VCC to 5V
// - GND to GND
// - Signal to A0

const int tempPin = A0;
const int fanPin = 8; // Use a relay or transistor for a real fan
const float thresholdC = 28.0; // Temperature threshold in Celsius

void setup() {
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Temperature-Activated Fan Ready");
}

void loop() {
  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100.0;
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print(" C - ");
  if (temperatureC > thresholdC) {
    digitalWrite(fanPin, HIGH); // Turn on fan/LED
    Serial.println("Fan ON");
  } else {
    digitalWrite(fanPin, LOW); // Turn off fan/LED
    Serial.println("Fan OFF");
  }
  delay(1000);
}
