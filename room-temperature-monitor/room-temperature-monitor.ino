// Room Temperature Monitor
// This project reads a temperature sensor and displays the temperature on the Serial Monitor.
//
// Wire your temperature sensor (like an LM35 or TMP36) to an analog pin.
//
// - VCC to 5V
// - GND to GND
// - Signal to A0
//
// The code assumes a TMP36 sensor. Adjust the math if you use a different sensor.

const int tempPin = A0; // Analog pin for temperature sensor

void setup() {
  Serial.begin(9600);
  Serial.println("Room Temperature Monitor");
}

void loop() {
  int sensorValue = analogRead(tempPin);
  // Convert the analog reading to voltage (0-5V)
  float voltage = sensorValue * (5.0 / 1023.0);
  // Convert voltage to temperature in Celsius for TMP36
  float temperatureC = (voltage - 0.5) * 100.0;
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" C");
  delay(1000); // Wait 1 second
}
