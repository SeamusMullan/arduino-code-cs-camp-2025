// Temperature Logger
// This project logs temperature readings to the Serial Monitor every 5 seconds.
//
// Connect your temperature sensor (like TMP36) to A0.
//
// - VCC to 5V
// - GND to GND
// - Signal to A0

const int tempPin = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("Time (s), Temperature (C)");
}

void loop() {
  static unsigned long startTime = millis();
  float seconds = (millis() - startTime) / 1000.0;
  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100.0;
  Serial.print(seconds);
  Serial.print(", ");
  Serial.println(temperatureC);
  delay(5000); // Log every 5 seconds
}
